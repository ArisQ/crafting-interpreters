#ifndef _VM_H_
#define _VM_H_

#include <cstdarg>
#include <chrono>

#include "config.h"
#include "chunk.h"
#include "object_manager.h"
#include "debug.h"
#include "clock.h"

#ifdef DEBUG_TRACE_EXECUTION
#include <iostream>
#endif

namespace vm {

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR,
} InterpretResult;

static const size_t FRAMES_MAX = 64;
static const size_t STACK_MAX = (FRAMES_MAX * (UINT8_MAX + 1));

struct CallFrame {
    ObjClosure *closure;
    uint8_t *ip;
    Value *slots; // pointer to stack frame base
};

class VM : public ObjOwner {
    CallFrame frames[FRAMES_MAX];
    int frameCount;
    CallFrame *frame;

    Value stack[STACK_MAX];
    Value *stackTop;
    Table globals;
    ObjUpvalue *openUpvalues;

    const ObjString *initString;

    inline const uint8_t readByte() { return *frame->ip++; }
    inline const uint16_t readShort() { return (readByte() << 8) + readByte(); }
    inline const Value readConstant() { return frame->closure->function->chunk->getConstant(readByte()); }
    inline ObjString *readString() { return AS_STRING(readConstant()); }

    void resetStack() {
        stackTop = stack;
        frameCount = 0;
        openUpvalues = nullptr;
    }
    inline void push(Value value) { *stackTop++ = value; }
    inline Value pop() { return *--stackTop; }
    inline Value &peek(int distance) { return stackTop[-1-distance]; }
    // inline void binaryOp(std::function<double(double,double)> op) {
    //     push(op(pop(), pop()));
    // }

    void runtimeError(const char* format, ...) {
        va_list args;
        va_start(args, format);
        vfprintf(stderr, format, args);
        va_end(args);

        fputs("\n", stderr);
        for (int i = frameCount - 1; i >= 0; --i) {
            auto frame = &frames[i];
            auto function = frame->closure->function;
            auto instruction = frame->ip - frame->closure->function->chunk->code -1;
            fprintf(stderr, "[line %d] in ", function->chunk->lines[instruction]);
            if(function->name==nullptr) {
                fprintf(stderr, "scripts\n");
            } else {
                fprintf(stderr, "%s()\n",function->name->chars);
            }
        }
        resetStack();
    }

    static inline bool isFalsey(const Value value) {
        return IS_NIL(value) || (IS_BOOL(value) && !AS_BOOL(value));
    }

    bool invoke(ObjString *name, int argCount) {
        auto receiver = peek(argCount);
        if(!IS_INSTANCE(receiver)) {
            runtimeError("Only instance have methods.");
            return false;
        }
        auto instance = AS_INSTANCE(receiver);

        Value value;
        if(instance->fields.get(name, &value)) {
            peek(argCount) = value;
            return callValue(value, argCount);
        }

        return invokeFromClass(instance->klass, name, argCount);
    }
    bool invokeFromClass(ObjClass *klass, ObjString *name, int argCount) {
        Value method;
        if(!klass->methods.get(name, &method)) {
            runtimeError("Undefined property '%s'.", name->chars);
            return false;
        }
        return call(AS_CLOSURE(method), argCount);
    }
    bool callValue(Value callee, int argCount) {
        if(IS_OBJ(callee)) {
            switch (OBJ_TYPE(callee)) {
            case OBJ_CLOSURE: return call(AS_CLOSURE(callee), argCount);
            case OBJ_NATIVE: {
                auto native = AS_NATIVE(callee);
                auto result = native(argCount, stackTop - argCount);
                stackTop -= (argCount+1);
                push(result);
                return true;
            }
            case OBJ_CLASS: {
                auto klass = AS_CLASS(callee);
                // stackTop[-argCount-1] = OBJ_VAL(NewInstance(klass));
                peek(argCount) = OBJ_VAL(NewInstance(klass));
                Value initializer;
                if(klass->methods.get(initString, &initializer)) {
                    return call(AS_CLOSURE(initializer), argCount);
                } else if (argCount != 0) {
                    runtimeError("Expected 0 arguments but got %d.", argCount);
                    return false;
                }
                return true;
            }
            case OBJ_BOUND_METHOD: {
                auto bound = AS_BOUND_METHOD(callee);
                // stackTop[-argCount-1] = bound->receiver;
                peek(argCount) = bound->receiver;
                return call(bound->method, argCount);
            }
            default: break;
            }
        }
        runtimeError("Can only call functions and classes.");
        return false;
    }
    bool call(ObjClosure *closure, int argCount) {
        auto function = closure->function;
        if(argCount!=function->arity) {
            runtimeError("Expect %d arguments but got %d.", function->arity, argCount);
            return false;
        }
        if(frameCount==FRAMES_MAX) {
            runtimeError("Stack overflow.");
            return false;
        }
        frame = &frames[frameCount++];
        frame->closure = closure;
        frame->ip = function->chunk->code;
        frame->slots = stackTop - argCount - 1;
        return true;
    }
    ObjUpvalue *captureUpvalue(Value *value) {
        ObjUpvalue *prevUpvalue = nullptr;
        ObjUpvalue *upvalue = openUpvalues;
        while (upvalue != nullptr && upvalue->location > value) {
            prevUpvalue=upvalue;
            upvalue = upvalue->next;
        }
        if (upvalue != nullptr && upvalue->location == value) {
            return upvalue;
        }
#ifdef DEBUG_TRACE_EXECUTION
        std::cout << "capture " << value << " '" << *value << "'" << std::endl;
#endif
        auto createdUpvalue = NewUpvalue(value);
        createdUpvalue->next=upvalue;
        if(prevUpvalue==nullptr) {
            openUpvalues = createdUpvalue;
        } else {
            prevUpvalue->next = createdUpvalue;
        }
        return createdUpvalue;
    }
    void closeUpvalues(Value *last) {
        while (openUpvalues != nullptr && openUpvalues->location >= last) {
            auto upvalue = openUpvalues;
#ifdef DEBUG_TRACE_EXECUTION
            std::cout << "closing " << upvalue->location << " '" << *upvalue->location << "'" << std::endl;
#endif
            upvalue->closed = *upvalue->location;
            upvalue->location = &upvalue->closed;
            openUpvalues = upvalue->next;
        }
    }

    bool bindMethod(ObjClass *klass, ObjString *name) {
        Value method;
        if(!klass->methods.get(name, &method)) {
            return false;
        }
        auto bound = NewBoundMethod(peek(0), AS_CLOSURE(method));
        pop(); // name
        push(OBJ_VAL(bound));
        return true;
    }

    void mark() {
        for (auto slot = stack; slot < stackTop; ++slot) {
            markValue(*slot);
        }
        for (int i = 0; i < frameCount; ++i) {
            markObj((Obj *)frames[i].closure);
        }
        for (ObjUpvalue *v = openUpvalues; v != nullptr; v = v->next) {
            markObj((Obj *)v);
        }
        // globals
        markTable(globals);
        markObj((Obj *)initString);
    }

public:
    static Value clockNative(int argCount, Value *args) {
        return NUMBER_VAL(clock());
    }
    VM(ObjPool &pool) : ObjOwner(pool), openUpvalues(nullptr), stackTop(stack), frame(nullptr), initString(NewString("init")) {
        resetStack();
        defineNative("clock", clockNative);
    }
    void defineNative(const char *name, NativeFn fn) {
        // globals.set(objMgr.NewString(name), OBJ_VAL(objMgr.NewNative(fn)));
        // for gc sake
        push(OBJ_VAL(NewString(name)));
        push(OBJ_VAL(NewNative(fn)));
        globals.set(AS_STRING(stack[0]), stack[1]);
        pop();
        pop();
    }
    InterpretResult interpret(ObjFunction *function) {
        resetStack();
        auto closure = NewClosure(function);
        auto objClosure = OBJ_VAL(closure);
        push(objClosure);
        callValue(objClosure, 0);
        return run();
    }
    InterpretResult run() {
// #define BINARY_OP(op) push(pop() op pop())
#define BINARY_OP(valueType, op)   \
    do {                \
        if(!IS_NUMBER(peek(0)) || !IS_NUMBER(peek(1))) { \
            runtimeError("Operands must be number"); \
            return INTERPRET_RUNTIME_ERROR; \
        } \
        auto b = AS_NUMBER(pop()); \
        auto a = AS_NUMBER(pop()); \
        push(valueType(a op b));   \
    } while (false)

        for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
            std::cout << "          ";
            for (Value *slot = stack; slot < stackTop; slot++) {
                std::cout << "[ " << *slot << " ]";
            }
            std::cout << std::endl;
            disassembleInstruction(std::cout, *frame->closure->function->chunk, (size_t)(frame->ip - frame->closure->function->chunk->code));
#endif
            uint8_t instruction;
            switch (instruction=readByte()) {
            case OP_CONSTANT: {
                push(readConstant());
                break;
            }
            case OP_NIL: push(NIL_VAL); break;
            case OP_TRUE: push(BOOL_VAL(true)); break;
            case OP_FALSE: push(BOOL_VAL(false)); break;
            // case OP_ADD: binaryOp(std::plus<double>()); break;
            case OP_EQUAL: {
                auto b = pop();
                auto a = pop();
                push(BOOL_VAL(a==b)); // push(BOOL_VAL(valuesEqual(a, b)));
                break;
            }
            case OP_LESS: BINARY_OP(BOOL_VAL, <); break;
            case OP_GREATER: BINARY_OP(BOOL_VAL, >); break;
            case OP_ADD: {
                if(IS_STRING(peek(0)) && IS_STRING(peek(1))) {
                    auto b = AS_STRING(pop());
                    auto a = AS_STRING(pop());
                    push(OBJ_VAL(NewString(a, b)));
                    // push(OBJ_VAL((*a) + (*b)));
                } else if(IS_NUMBER(peek(0)) && IS_NUMBER(peek(1))) {
                    auto b = AS_NUMBER(pop());
                    auto a = AS_NUMBER(pop());
                    push(NUMBER_VAL(a + b));
                } else {
                    runtimeError("Operands must be two numbers or two strings.");
                    return INTERPRET_RUNTIME_ERROR;
                }
                break;
            }
            case OP_SUBSTRACT: BINARY_OP(NUMBER_VAL, -); break;
            case OP_MULTIPLY: BINARY_OP(NUMBER_VAL, *); break;
            case OP_DIVIDE: BINARY_OP(NUMBER_VAL, /); break;
            case OP_NEGATE:
                if (!IS_NUMBER(peek(0))) {
                    runtimeError("Operand must be number.");
                    return INTERPRET_RUNTIME_ERROR;
                }
                push(NUMBER_VAL(-AS_NUMBER(pop())));
                break;
            case OP_NOT:
                push(BOOL_VAL(isFalsey(pop())));
                break;
            case OP_PRINT:
                std::cout << pop() << std::endl;
                break;
            case OP_POP: pop(); break;
            case OP_DEFINE_GLOBAL: {
                auto name = readString();
                globals.set(name, peek(0));
                pop();
                break;
            }
            case OP_GET_GLOBAL: {
                auto name = readString();
                Value v;
                if(!globals.get(name, &v)) {
                    runtimeError("Undefined variable '%s'.", name->chars);
                    return INTERPRET_RUNTIME_ERROR;
                }
                push(v);
                break;
            }
            case OP_SET_GLOBAL: {
                auto name = readString();
                Value v;
                if(globals.set(name, peek(0))) {
                    // delete会产生tombstone，采用get&set?
                    // 大部分情况key都存在，不存在是异常，会返回runtime error
                    // 因此直接set比较好
                    globals.remove(name);
                    runtimeError("Undefined variable '%s'.", name->chars);
                    return INTERPRET_RUNTIME_ERROR;
                }
                break;
            }
            case OP_GET_LOCAL: {
                push(frame->slots[readByte()]);
                break;
            }
            case OP_SET_LOCAL: {
                frame->slots[readByte()] = peek(0);
                break;
            }
            case OP_GET_UPVALUE: {
                auto slot = readByte();
                push(*frame->closure->upvalues[slot]->location);
                break;
            }
            case OP_SET_UPVALUE: {
                auto slot = readByte();
                *frame->closure->upvalues[slot]->location = peek(0);
                break;
            }
            case OP_JUMP_IF_ELSE: {
                uint16_t offset = readShort();
                if (isFalsey(peek(0))) { // 不pop
                    frame->ip += offset;
                }
                break;
            }
            case OP_JUMP: {
                uint16_t offset = readShort();
                frame->ip += offset;
                break;
            }
            case OP_LOOP: {
                uint16_t offset = readShort();
                frame->ip -= offset;
                break;
            }
            case OP_CALL: {
                auto argCount = readByte();
                if(!callValue(peek(argCount), argCount)) {
                    return INTERPRET_RUNTIME_ERROR;
                }
                break;
            }
            case OP_INVOKE: {
                auto method = readString();
                auto argCount = readByte();
                if(!invoke(method, argCount)) {
                    return INTERPRET_RUNTIME_ERROR;
                }
                // frame = &frames[--frameCount];
                break;
            }
            case OP_CLOSURE: {
                auto function = AS_FUNCTION(readConstant());
                auto closure = NewClosure(function);
                push(OBJ_VAL(closure));
                for (int i = 0; i < closure->upvalueCount; ++i) {
                    auto isLocal = readByte();
                    auto index = readByte();
                    if (isLocal) {
                        closure->upvalues[i] = captureUpvalue(frame->slots + index);
                    } else {
                        closure->upvalues[i] = frame->closure->upvalues[index];
                    }
                }
                break;
            }
            case OP_CLOSE_UPVALUE: {
                closeUpvalues(stackTop-1);
                pop();
                break;
            }
            case OP_RETURN: {
                auto result = pop();
                closeUpvalues(frame->slots);
                --frameCount;
                if(frameCount == 0 ) {
                    pop();
                    return INTERPRET_OK;
                }
                stackTop = frame->slots;
                push(result);
                frame = &frames[frameCount - 1];
                break;
            }
            case OP_CLASS: {
                push(OBJ_VAL(NewClass(readString())));
                break;
            }
            case OP_INHERIT: {
                auto superValue = peek(0);
                auto klass = AS_CLASS(peek(1));
                if(!IS_CLASS(superValue)) {
                    runtimeError("Superclass must be a class.");
                    return INTERPRET_RUNTIME_ERROR;
                }
                klass->methods.addAll(&AS_CLASS(superValue)->methods);
                pop(); // super
                break;
            }
            case OP_METHOD: {
                auto method = peek(0);
                auto klass = AS_CLASS(peek(1));
                klass->methods.set(readString(), method);
                pop();
                break;
            }
            case OP_GET_PROPERTY: {
                if(!IS_INSTANCE(peek(0))) {
                    runtimeError("Only instance have properties.");
                    return INTERPRET_RUNTIME_ERROR;
                }
                auto instance = AS_INSTANCE(peek(0));
                auto name = readString();
                Value v(NIL_VAL);
                if (instance->fields.get(name, &v)) {
                    pop();
                    push(v);
                    break;
                }
                if(!bindMethod(instance->klass, name)) {
                    runtimeError("Undefined property '%s'.", name->chars);
                    return INTERPRET_RUNTIME_ERROR;
                }
                break;
            }
            case OP_SET_PROPERTY: {
                auto instance = AS_INSTANCE(peek(1));
                instance->fields.set(readString(), peek(0));
                auto value = pop();
                pop();
                push(value);
                break;
            }
            default:
                runtimeError("Invalid instruction %d", instruction);
                return INTERPRET_RUNTIME_ERROR;
            }
        }
    }
#undef BINARY_OP
};
}

#endif // _VM_H_