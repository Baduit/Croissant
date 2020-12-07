#include <iostream>
#include <utility>
#include <cassert>
#include <cstdint>

#include <boost_ut/ut.hpp>
#include <Croissant/Number.hpp>

using namespace boost::ut;

void number_base()
{
    Croissant::NumberBase<int32_t> a = 3;
	Croissant::NumberBase<int32_t> b = 4;

	expect(*(a + b) == 7);

}

int main()
{
	"number_base"_test = number_base;
}