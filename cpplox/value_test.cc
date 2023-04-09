#include <iostream>

#include <cmath>
#include "value.h"

int main()
{
    auto a = std::make_shared<NilValue>();
    auto b = std::make_shared<NilValue>();
    // std::cout << (n == nullptr) << std::endl;
    std::cout << (a == b) << std::endl;
    std::cout << (floor(2.3)==2.3) << std::endl;
    std::cout << (round(2)==2) << std::endl;
}