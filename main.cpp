#include "rust_module/include/rust_module.h"

#include <iostream>

int main()
{
    []{ std::cout << "And the result is : " << greet_from_rust() << std::endl; }();
    return 0;
}
