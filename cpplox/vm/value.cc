#include <iostream>
#include "value.h"

namespace vm
{
    std::ostream &operator<<(std::ostream &os, const Value &v)
    {
        switch (v.type)
        {
        case VAL_NUMBER: os<<v.as.number; break;
        case VAL_BOOL: os<<(v.as.boolean?"true":"false"); break;
        case VAL_NIL: os<<"nil"; break;
        case VAL_OBJ: os<<v.as.obj; break;
        default: break;
        }
        return os;
    }

    bool operator==(const Value l, const Value r) {
        return valuesEqual(l, r);
    }
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
            return ls->length==rs->length && memcmp(ls->chars, rs->chars, ls->length) == 0;
        }
        default: break;
        }
        return false;
    }
}