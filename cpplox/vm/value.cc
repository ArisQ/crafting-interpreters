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
        default: break;
        }
        return os;
    }
}