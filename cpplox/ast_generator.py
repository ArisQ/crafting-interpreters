#!/usr/bin/env python3

from enum import Enum

class field():
    def __init__(self, f: str):
        # print( f.strip().split(' '))
        is_pointer = False
        is_list = False
        type, name = f.strip().split(' ')
        if type.startswith('*'):
            is_pointer = True
            type = type[1:]
        if type.endswith('[]'):
            is_list = True
            type = type[:-2]
        self.is_pointer = is_pointer
        self.is_list = is_list
        self.type = type
        self.name = name

    @property
    def type_str(self):
        t = self.type
        if self.is_pointer:
            t = 'std::shared_ptr<{}>'.format(t)
        if self.is_list:
            t = 'std::vector<{}>'.format(t)
        return t

    def __repr__(self) -> str:
        return self.type + ' ' +self.name

class child():
    def __init__(self, base: str,line: str):
        print(line)
        if not line.startswith('// '):
            raise Exception('invalid template line', line)
        line = line[3:].strip()
        name, fields = line.split(':')
        self.base = base
        self.name = name.strip()
        self.fields = [field(f) for f in fields.split(',')]

    def __repr__(self) -> str:
        return self.name + ' ' + str(self.fields)


def generate_class(c: child):
    yield f'struct {c.name}: public {c.base} {{'

    for f in c.fields:
        yield f'    {f.type_str} {f.name};'

    yield '' # blank line

    yield f'    std::shared_ptr<void> _accept(_{c.base}Visitor * const v) {{ return v->visit{c.name}(this); }}'

    # constructor
    yield '    {}({}): {} {{}}'.format(
        c.name,
        ', '.join([f.type_str+' '+f.name for f in c.fields]),
        ', '.join(['{}({})'.format(f.name, f.name) for f in c.fields]),
    )

    yield '};'

def generate(className: str, tpl: list[str]):
    children = [child(className, l) for l in tpl] # parse

    yield '// class declaration'
    for c in children:
        yield f'class {c.name};'
    yield ''

    yield '// templated vistor for inherit'
    yield 'template <typename T>'
    yield f'class {className}Visitor {{'
    yield 'public:'
    for c in children:
        yield f'    virtual T visit{c.name}({c.name} *) = 0;'
    yield '};'
    yield '' # blank line

    yield '// internal general vistor for virtual accept'
    yield f'class _{className}Visitor {{'
    yield 'public:'
    for c in children:
        yield f'    virtual std::shared_ptr<void> visit{c.name}({c.name} *) = 0;'
    yield '};'
    yield '' # blank line

    # convertor会对vistor的结果做一次拷贝
    yield '// templated vistor to internal vistor'
    yield 'template <typename T>'
    yield f'class {className}VisitorConvertor: public _{className}Visitor {{'
    yield f'    {className}Visitor<T> *v;'
    yield 'public:'
    yield f'    {className}VisitorConvertor({className}Visitor<T> *v): v(v) {{}}'
    for c in children:
        # yield f'    std::shared_ptr<void> visit{c.name}({c.name} *e) {{ return std::static_pointer_cast<void>(std::make_shared<T>( v->visit{c.name}(e))); }}'
        yield f'    std::shared_ptr<void> visit{c.name}({c.name} *e) {{'
        yield f'        return std::static_pointer_cast<void>(std::make_shared<T>(v->visit{c.name}(e)));'
        yield f'    }}'
    yield '};'
    yield '' # blank line

    # 返回值类型为shared_ptr的模板特化
    yield '// 返回值类型为shared_ptr的模板特化'
    yield 'template <typename T>'
    yield f'class {className}VisitorConvertor<std::shared_ptr<T>>: public _{className}Visitor {{'
    yield f'    {className}Visitor<std::shared_ptr<T>> *v;'
    yield 'public:'
    yield f'    {className}VisitorConvertor({className}Visitor<std::shared_ptr<T>> *v): v(v) {{}}'
    for c in children:
        # yield f'    std::shared_ptr<void> visit{c.name}({c.name} *e) {{ return std::static_pointer_cast<void>(v->visit{c.name}(e)); }}'
        yield f'    std::shared_ptr<void> visit{c.name}({c.name} *e) {{'
        yield f'        return std::static_pointer_cast<void>(v->visit{c.name}(e));'
        yield f'    }}'
    yield '};'
    yield '' # blank line

    # 返回值类型为void的模板特化
    yield '// 返回值类型为void的模板特化'
    yield 'template <>'
    yield f'class {className}VisitorConvertor<void>: public _{className}Visitor {{'
    yield f'    {className}Visitor<void> *v;'
    yield 'public:'
    yield f'    {className}VisitorConvertor({className}Visitor<void> *v): v(v) {{}}'
    for c in children:
        # yield f'    std::shared_ptr<void> visit{c.name}({c.name} *e) {{ return std::static_pointer_cast<void>(v->visit{c.name}(e)); }}'
        yield f'    std::shared_ptr<void> visit{c.name}({c.name} *e) {{'
        yield f'        v->visit{c.name}(e);'
        yield f'        return nullptr;'
        yield f'    }}'
    yield '};'
    yield '' # blank line

    yield f'''// {className} definition
struct {className} {{
    template <typename T>
    T accept({className}Visitor<T> *const v) {{
        auto visitor = {className}VisitorConvertor<T>(v);
        return *(std::static_pointer_cast<T>(this->_accept(&visitor)));
    }}

    template <typename T>
    std::shared_ptr<T> accept({className}Visitor<std::shared_ptr<T>> *const v) {{
        auto visitor = {className}VisitorConvertor<std::shared_ptr<T>>(v);
        return std::static_pointer_cast<T>(this->_accept(&visitor));
    }}

    // c++ 成员函数不支持template + virtual
    // 分成两步
    // virtual的_accept用于继承，使用通用类型的visitor
    // 基类实现template的accept，不需要子类继承，仅做类型转换后调用使用通用类型的virtual的_accept
    virtual std::shared_ptr<void> _accept(_{className}Visitor* const) = 0;
}};
template <>
inline void {className}::accept<void>({className}Visitor<void> *const v) {{
    auto visitor = {className}VisitorConvertor<void>(v);
    this->_accept(&visitor);
}}
'''

    for c in children:
        yield from generate_class(c)
        yield '' # blank line


class State(Enum):
    RAW = 1
    TEMPLATE = 2
    GENERATED = 3

def defineAst(className: str):
    fileName=className.lower()
    with open(fileName+'.src.h') as tpl, open(fileName+'.gen.h', 'w') as gen:
        gen.write('// GENERATED BY ast_generator. DO NOT EDIT.\n')
        state = State.RAW
        tpl_str = []
        for l in tpl:
            # print(state, l, end='') # dump line state
            if state == State.RAW:
                gen.write(l)
                if l.startswith('// GENERATOR_START'):
                    state = State.TEMPLATE
            elif state == State.TEMPLATE:
                gen.write(l)
                if l.startswith('// GENERATED'):
                    gen.writelines([l+'\n' for l in generate(className, tpl_str)])
                    tpl_str = []
                    state = State.GENERATED
                    continue # don't append anchor line to templates
                tpl_str.append(l)
            elif state == State.GENERATED:
                # ignore generated
                if l.startswith('// GENERATOR_END'):
                    gen.write(l)
                    state = State.RAW
            else:
                raise Exception('invalid template status')


defineAst('Stmt')
defineAst('Expr')
