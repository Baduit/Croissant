#pragma once

#include <concepts>
#include <compare>

namespace Croissant
{

template <typename T>
concept NumberBuiltin = std::integral<T> || std::floating_point<T>;

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

template <NumberBuiltin N>
struct NumberBase
{
	using ValueType = N;

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

	bool operator==(const NumberBase&) const = default;
	auto operator<=>(const NumberBase&) const = default;


	ValueType value = {};
};

} // namespace Croissant
