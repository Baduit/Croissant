#include <iostream>
#include <utility>
#include <cassert>
#include <string>

#include <boost_ut/ut.hpp>
#include <Croissant/Croissant.hpp>

using namespace boost::ut;

CROISSANT_DISABLE_PARENTHESES_WARNING

void equality()
{
	Croissant::Value<int> a(5);
	Croissant::Value<int> b(5);
	Croissant::Value<int> c(6);
	
	expect(bool(a == b)) << "Simple comparison between 2 croissant value";
	expect(bool(5 == a)) << "Simple comparison between a value and a croissant value";
	expect(!bool(6 == b)) << "Simple comparison between a croissant value and a value";

	expect(bool(a == b == 5)) << "Chained comparison between a croissant value, an other croissant value and a value";
	expect(!bool(a == b == 6)) << "Chained comparison between a croissant value, an other croissant value and a value";
	expect(!bool(a == 7 == 5)) << "Chained comparison between a croissant value, a value and an other value";

	expect(bool(a == b == a)) << "Chained comparison between 3 croissant values";
	expect(!bool(a == b == c)) << "Chained comparison between 3 croissant values";
	expect(!bool(c == a == b)) << "Chained comparison between 3 croissant values";
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

struct StructForTest {};

void construction_and_assigment()
{
	{
		Croissant::Value<std::string> str;
		str = "lol";
	}
	{
		std::size_t size = 2;
		Croissant::Value<std::string> str("lol", size);
	}
}

void string_literals()
{
	using namespace Croissant::StringLiterals;
	{
		auto strv1 = "Salut moi c'est Lena"_sv;
		auto str2 = "Salut moi c'est Lena"_s;
		auto strv3 = "Salut moi c'est Lena"_sv;
		auto strv4 = "Salut moi c'est pas Lena"_sv;

		expect(bool(strv1 == str2));
		expect(!bool(strv1 == strv4));
		expect(bool(strv1 == str2 == strv3));
		expect(!bool(strv1 == str2 == strv4));
	}
}

int main()
{
	"equality"_test = equality;
	"more"_test = more;
	"less"_test = less;
	"construction_and_assigment"_test = construction_and_assigment;
	"literals"_test = string_literals;
}