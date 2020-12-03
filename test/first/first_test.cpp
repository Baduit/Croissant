#include <iostream>
#include <utility>
#include <cassert>

#include <boost_ut/ut.hpp>
#include <Croissant/Croissant.hpp>

using namespace boost::ut;

void comparaisons()
{
	expect((true) >> fatal) << "If this test fails, the it stops here.";
	CroissantValue<int> a(5);
    CroissantValue<int> b(5);
    CroissantValue<int> c(6);
    
    expect(bool(a == b)) << "Simple comparaison between 2 croissant value";
    expect(bool(5 == a)) << "Simple comparaison between a value and a croissant value";
    expect(bool(!(6 == b))) << "Simple comparaison between a croissant value and a value";

    expect(bool((a == b == 5))) << "Chained comparaison between a croissant value, an other croissant value and a value";
    expect(bool(!(a == b == 6))) << "Chained comparaison between a croissant value, an other croissant value and a value";
    expect(bool(!(a == 7 == 5))) << "Chained comparaison between a croissant value, a value and an othervalue";

    expect(bool((a == b == a))) << "Chained comparaison between 3 croissant value";
    expect(bool(!(a == b == c))) << "Chained comparaison between 3 croissant value";
    expect(bool(!(c == a == b))) << "Chained comparaison between 3 croissant value";
}

int main()
{
	"comparaisons"_test = comparaisons;
}