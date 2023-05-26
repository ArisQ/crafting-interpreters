#include <iostream>
#include "value.h"
#include "object.h"

namespace vm
{
    std::ostream &operator<<(std::ostream &os, const ValuePrinter &p) {
        auto v = p.v;
        if(IS_BOOL(v)) {
            os << (AS_BOOL(v)? "true" : "false");
        } if(IS_NIL(v)) {
            os << "nil";
        } if(IS_NUMBER(v)) {
            os << AS_NUMBER(v);
        } if(IS_OBJ(v)) {
            os << AS_OBJ(v);
        }
        return os;
    }

#ifdef NAN_BOXING
    bool valuesEqual(const Value l, const Value r) {
        if(IS_NUMBER(l) && IS_NUMBER(r)) {
            return AS_NUMBER(l) == AS_NUMBER(r);
        }
        return l == r;
    }
#else
    bool valuesEqual(const Value l, const Value r) {
        if (l.type!=r.type) return false;
        switch (l.type)
        {
        case VAL_BOOL: return AS_BOOL(l) == AS_BOOL(r);
        case VAL_NIL: return true;
        case VAL_NUMBER: return AS_NUMBER(l) == AS_NUMBER(r);
        case VAL_OBJ: {
            auto ls = AS_STRING(l);
            auto rs = AS_STRING(r);
            return ls == rs; // strings are interned
        }
        default: break;
        }
        return false;
    }
    bool operator==(const Value l, const Value r) {
        return valuesEqual(l, r);
    }
#endif
}