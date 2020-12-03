#include <iostream>
#include <compare>
#include <concepts>
#include <type_traits>
#include <string_view>
#include <cassert>

#include <Croissant/Croissant.hpp>

int main()
{
    Croissant::Value<int> a(5);
    Croissant::Value<int> b(5);

    if (a == b == 5)
        std::cout << "true" << std::endl;
    else
        std::cout << "false" << std::endl;
}