#include <cmath>
#include "value.h"

template<> std::string Val<std::string>::toString() {
    return "\"" + v + "\"";
}
template<> std::string Val<double>::toString() {
    if (floor(v)==v) {
        return string_format("%d", int(v));
    }
    return string_format("%lf", v);
}
template<> std::string Val<bool>::toString() { return v?"true":"false"; }
// template<> std::string Val<std::nullptr_t>::toString() { return "nil"; }

