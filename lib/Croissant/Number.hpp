#pragma once

#include <concepts>
#include <compare>

#include <Croissant/OperatorsConcept.hpp>

namespace Croissant
{

template <typename A, typename R>
concept CanBeConstructTo =
	requires (A a)
	{
		{ R(a) };
	};

template <typename A, typename R>
concept CanBeAssignTo =
	requires (A a, R r)
	{
		{ r = a };
	};

template <typename T, typename U, typename F>
concept OperatorCompatible =
	requires(T t, U u, F f)
	{
		f(t, u);
	};

template <NumberBuiltin N>
struct NumberBase
{
	using ValueType = N;

	/*
	** Constructor and assigment
	*/
	NumberBase() = default;

	NumberBase(const NumberBase&) = default;
	NumberBase& operator=(const NumberBase&) = default;

	NumberBase(NumberBase&&) = default;
	NumberBase& operator=(NumberBase&&) = default;


	template <CanBeConstructTo<ValueType> T>
	NumberBase(T n):
		value(n)
	{}

	template <CanBeAssignTo<ValueType> T>
	NumberBase& operator=(T n)
	{
		value = n;
		return *this;
	}

	/*
	** Access underlying value
	*/
	ValueType& get() { return value; }
	ValueType get() const { return value; }

	ValueType& operator*() { return value; }
	ValueType operator*() const { return value; }

	/*
	** Comparison operators
	*/
	bool operator==(const NumberBase&) const = default;
	auto operator<=>(const NumberBase&) const = default;
	
	/*
	** Arithmetic assigment operators
	*/
	// +=
	template <AddAssigmentCompatible<ValueType> U>
	auto operator+=(NumberBase<U> u) { value += u.value; return *this; }

	template <AddAssigmentCompatible<ValueType> U>
	auto operator+=(U u) { value += u; return *this;  }


	// -=
	template <LessAssigmentCompatible<ValueType> U>
	auto operator-=(NumberBase<U> u) { value -= u.value; return *this;  }

	template <LessAssigmentCompatible<ValueType> U>
	auto operator-=(U u) { value -= u; return *this;  }


	// *=
	template <MultiplyAssigmentCompatible<ValueType> U>
	auto operator*=(NumberBase<U> u) { value *= u.value; return *this;  }

	template <MultiplyAssigmentCompatible<ValueType> U>
	auto operator*=(U u) { return value *= u; return *this;  }


	// /=
	template <DivideAssigmentCompatible<ValueType> U>
	auto operator/=(NumberBase<U> u) { value /= u.value; return *this;  }

	template <DivideAssigmentCompatible<ValueType> U>
	auto operator/=(U u) { value /= u; return *this;  }


	// %=
	template <ModuloAssigmentCompatible<ValueType> U>
	auto operator%=(NumberBase<U> u) { value %= u.value; return *this;  }

	template < ModuloAssigmentCompatible<ValueType> U>
	auto operator%=(U u) { value %= u; return *this;  }


	/*
	** Bitwise assigment operators
	*/
	// &=
	template <BitAndAssigmentCompatible<ValueType> U>
	auto operator&=(NumberBase<U> u) { value &= u.value; return *this;  }

	template <BitAndAssigmentCompatible<ValueType> U>
	auto operator&=(U u) { return value &= u; return *this;  }


	// |=
	template <BitOrAssigmentCompatible<ValueType> U>
	auto operator|=(NumberBase<U> u) { value |= u.value; return *this;  }

	template <BitOrAssigmentCompatible<ValueType> U>
	auto operator|=(U u) { value |= u; return *this;  }


	// ^=
	template <BitXorAssigmentCompatible<ValueType> U>
	auto operator^=(NumberBase<U> u) { value ^= u.value; return *this;  }

	template < BitXorAssigmentCompatible<ValueType> U>
	auto operator^=(U u) { value ^= u; return *this;  }

	/*
	** Shift assigment operators
	*/
	// >>=
	template <ShiftRightAssigmentCompatible<ValueType> U>
	auto operator>>=(NumberBase<U> u) { value >>= u.value; return *this;  }

	template <ShiftRightAssigmentCompatible<ValueType> U>
	auto operator>>=(U u) { value >>= u; return *this;  }


	// <<=
	template <ShiftLeftAssigmentCompatible<ValueType> U>
	auto operator<<=(NumberBase<U> u) { value <<= u.value; return *this;  }

	template < ShiftLeftAssigmentCompatible<ValueType> U>
	auto operator<<=(U u) { value <<= u; return *this;  }

	ValueType value = {};
};

/*
** Arithmetic operators
*/
// +
template <typename T, AddCompatible<T> U>
auto operator+(NumberBase<T> t, NumberBase<U> u) { return NumberBase<decltype(*t + *u)>(*t + *u); }

template <typename T, AddCompatible<T> U>
auto operator+(NumberBase<T> t, U u) { return NumberBase<decltype(*t + u)>(*t + u); }

template <typename T, AddCompatible<T> U>
auto operator+(T t, NumberBase<U> u) { return NumberBase<decltype(t + *u)>(t + *u); }

// -
template <typename T, LessCompatible<T> U>
auto operator-(NumberBase<T> t, NumberBase<U> u) { return NumberBase<decltype(*t - *u)>(*t - *u); }

template <typename T, LessCompatible<T> U>
auto operator-(NumberBase<T> t, U u) { return NumberBase<decltype(*t - u)>(*t - u); }

template <typename T, LessCompatible<T> U>
auto operator-(T t, NumberBase<U> u) { return NumberBase<decltype(t - *u)>(t - *u); }

// *
template <typename T, MultiplyCompatible<T> U>
auto operator*(NumberBase<T> t, NumberBase<U> u) { return NumberBase<decltype(*t * *u)>(*t * *u); }

template <typename T, MultiplyCompatible<T> U>
auto operator*(NumberBase<T> t, U u) { return NumberBase<decltype(*t * u)>(*t * u); }

template <typename T, MultiplyCompatible<T> U>
auto operator*(T t, NumberBase<U> u) { return NumberBase<decltype(t * *u)>(t * *u); }

// /
template <typename T, DivideCompatible<T> U>
auto operator/(NumberBase<T> t, NumberBase<U> u) { return NumberBase<decltype(*t / *u)>(*t / *u); }

template <typename T, DivideCompatible<T> U>
auto operator/(NumberBase<T> t, U u) { return NumberBase<decltype(*t / u)>(*t / u); }

template <typename T, DivideCompatible<T> U>
auto operator/(T t, NumberBase<U> u) { return NumberBase<decltype(t / *u)>(t / *u); }

// %
template <typename T, ModuloCompatible<T> U>
auto operator%(NumberBase<T> t, NumberBase<U> u) { return NumberBase<decltype(*t % *u)>(*t % *u); }

template <typename T, ModuloCompatible<T> U>
auto operator%(NumberBase<T> t, U u) { return NumberBase<decltype(*t % u)>(*t % u); }

template <typename T, ModuloCompatible<T> U>
auto operator%(T t, NumberBase<U> u) { return NumberBase<decltype(t % *u)>(t % *u); }

// -
template <NegateCompatible T>
auto operator-(NumberBase<T> t) { return NumberBase<T>(-(*t)); }

/*
** Bitwise operators
*/
// &
template <typename T, BitAndCompatible<T> U>
auto operator&(NumberBase<T> t, NumberBase<U> u) { return NumberBase<decltype(*t & *u)>(*t & *u); }

template <typename T, BitAndCompatible<T> U>
auto operator&(NumberBase<T> t, U u) { return NumberBase<decltype(*t & u)>(*t & u); }

template <typename T, BitAndCompatible<T> U>
auto operator&(T t, NumberBase<U> u) { return NumberBase<decltype(t & *u)>(t & *u); }

// |
template <typename T, BitOrCompatible<T> U>
auto operator|(NumberBase<T> t, NumberBase<U> u) { return NumberBase<decltype(*t | *u)>(*t | *u); }

template <typename T, BitOrCompatible<T> U>
auto operator|(NumberBase<T> t, U u) { return NumberBase<decltype(*t | u)>(*t | u); }

template <typename T, BitOrCompatible<T> U>
auto operator|(T t, NumberBase<U> u) { return NumberBase<decltype(t | *u)>(t | *u); }

// ^
template <typename T, BitXorCompatible<T> U>
auto operator^(NumberBase<T> t, NumberBase<U> u) { return NumberBase<decltype(*t ^ *u)>(*t ^ *u); }

template <typename T, BitXorCompatible<T> U>
auto operator^(NumberBase<T> t, U u) { return NumberBase<decltype(*t ^ u)>(*t ^ u); }

template <typename T, BitXorCompatible<T> U>
auto operator^(T t, NumberBase<U> u) { return NumberBase<decltype(t ^ *u)>(t ^ *u); }

/*
** Logical operators
*/
// &&
template <typename T, LogicAndCompatible<T> U>
auto operator&&(NumberBase<T> t, NumberBase<U> u) { return NumberBase<decltype(*t && *u)>(*t && *u); }

template <typename T, LogicAndCompatible<T> U>
auto operator&&(NumberBase<T> t, U u) { return NumberBase<decltype(*t && u)>(*t && u); }

template <typename T, LogicAndCompatible<T> U>
auto operator&&(T t, NumberBase<U> u) { return NumberBase<decltype(t && *u)>(t && *u); }

// ||
template <typename T, LogicOrCompatible<T> U>
auto operator||(NumberBase<T> t, NumberBase<U> u) { return NumberBase<decltype(*t || *u)>(*t || *u); }

template <typename T, LogicOrCompatible<T> U>
auto operator||(NumberBase<T> t, U u) { return NumberBase<decltype(*t || u)>(*t || u); }

template <typename T, LogicOrCompatible<T> U>
auto operator||(T t, NumberBase<U> u) { return NumberBase<decltype(t || *u)>(t || *u); }

// !
template <LogicNotCompatible T>
auto operator!(NumberBase<T> t) { return NumberBase<T>(!(*t)); }

/*
** Shift operators
*/
// >>
template <typename T, ShiftRightCompatible<T> U>
auto operator>>(NumberBase<T> t, NumberBase<U> u) { return NumberBase<decltype(*t >> *u)>(*t >> *u); }

template <typename T, ShiftRightCompatible<T> U>
auto operator>>(NumberBase<T> t, U u) { return NumberBase<decltype(*t >> u)>(*t >> u); }

template <typename T, ShiftRightCompatible<T> U>
auto operator>>(T t, NumberBase<U> u) { return NumberBase<decltype(t >> *u)>(t >> *u); }

// <<
template <typename T, ShiftLeftCompatible<T> U>
auto operator<<(NumberBase<T> t, NumberBase<U> u) { return NumberBase<decltype(*t << *u)>(*t << *u); }

template <typename T, ShiftLeftCompatible<T> U>
auto operator<<(NumberBase<T> t, U u) { return NumberBase<decltype(*t << u)>(*t << u); }

template <typename T, ShiftLeftCompatible<T> U>
auto operator<<(T t, NumberBase<U> u) { return NumberBase<decltype(t << *u)>(t << *u); }

} // namespace Croissant
