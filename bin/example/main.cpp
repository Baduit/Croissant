#include <iostream>
#include <compare>
#include <concepts>
#include <type_traits>
#include <string_view>
#include <cassert>

#include <Croissant/Croissant.hpp>

int main()
{
	using namespace Croissant;
	using namespace Croissant::IntegerLiterals;

	Int a = 5;
	auto b = 6_i;

	if (a < b <= 6)
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;
}