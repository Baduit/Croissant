#include <iostream>
#include <utility>
#include <cassert>
#include <cstdint>

#include <boost_ut/ut.hpp>
#include <Croissant/Croissant.hpp>

using namespace boost::ut;

void number_base()
{
    Croissant::Value<int32_t> a = 3;
	Croissant::Value<int32_t> b = 4;

	expect(*(a + b) == 7);
	expect(*(a + 4) == 7);

	expect((a != b));
	expect(bool(a < b));

	expect(bool(a == 3));
	expect(bool(4 == b));

	a += 3;
	expect(bool(a == 6));

	a += b;
	expect(bool(10 == a));
}

int main()
{
	"number_base"_test = number_base;
}