#include "clock.h"
#include <chrono>

namespace vm {
using namespace std::chrono;
double clock() {
    uint64_t ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    return ms / 1000.0;
}
}