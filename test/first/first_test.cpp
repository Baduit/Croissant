#include <iostream>
#include <utility>
#include <cassert>

#include <boost_ut/ut.hpp>
#include <Croissant/Croissant.hpp>

using namespace boost::ut;

void equality()
{
	Croissant::Value<int> a(5);
    Croissant::Value<int> b(5);
    Croissant::Value<int> c(6);
    
    expect(bool(a == b)) << "Simple comparaison between 2 croissant value";
    expect(bool(5 == a)) << "Simple comparaison between a value and a croissant value";
    expect(!bool(6 == b)) << "Simple comparaison between a croissant value and a value";

    expect(bool(a == b == 5)) << "Chained comparaison between a croissant value, an other croissant value and a value";
    expect(!bool(a == b == 6)) << "Chained comparaison between a croissant value, an other croissant value and a value";
    expect(!bool(a == 7 == 5)) << "Chained comparaison between a croissant value, a value and an other value";

    expect(bool(a == b == a)) << "Chained comparaison between 3 croissant values";
    expect(!bool(a == b == c)) << "Chained comparaison between 3 croissant values";
    expect(!bool(c == a == b)) << "Chained comparaison between 3 croissant values";
}

void more()
{
    Croissant::Value<int> a(1);
    Croissant::Value<int> b(5);
    Croissant::Value<int> c(6);

    expect(bool(c > b > a));
    expect(!bool(a >= b));
    expect(bool(15 > b > 1));
}

void less()
{
    Croissant::Value<int> a(1);
    Croissant::Value<int> b(5);
    Croissant::Value<int> c(6);

    expect(!bool(c < b < a));
    expect(bool(a < b));
    expect(bool(5 <= b < 10));
}

int main()
{
	"equality"_test = equality;
    "more"_test = more;
    "less"_test = less;
}