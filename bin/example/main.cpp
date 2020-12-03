#include <iostream>
#include <compare>
#include <concepts>
#include <type_traits>
#include <string_view>
#include <cassert>

#include <Croissant/Croissant.hpp>

int main()
{
    CroissantValue<int> a(5);
    CroissantValue<int> b(5);

    if (a == b == 5)
        std::cout << "true" << std::endl;
    else
        std::cout << "false" << std::endl;
}