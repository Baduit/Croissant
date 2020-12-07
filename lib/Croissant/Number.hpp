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

	/*
	** Bitwise assigment operators
	*/

	/*
	** Shift assigment operators
	*/

	ValueType value = {};
};

/*
** Arithmetic operators
*/
template <typename T, AddCompatible<T> U>
auto operator+(NumberBase<T> t, NumberBase<U> u) { return NumberBase<decltype(*t + *u)>(*t + *u); }

template <typename T, AddCompatible<T> U>
auto operator+(NumberBase<T> t, U u) { return NumberBase<decltype(*t + u)>(*t + u); }

template <typename T, AddCompatible<T> U>
auto operator+(T t, NumberBase<U> u) { return NumberBase<decltype(t + *u)>(t + *u); }

/*
** Bitwise operators
*/

/*
** Logical operators
*/


/*
** Shift operators
*/

} // namespace Croissant
