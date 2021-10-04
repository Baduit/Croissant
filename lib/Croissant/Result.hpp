#pragma once

#include <iostream>
#include <compare>
#include <concepts>
#include <type_traits>

#include <Croissant/Tags.hpp>

namespace Croissant
{

// Do not store a Result, the const* can easily become invalid
template <ComparisonTag T, typename Value>
struct Result : public ResultTag
{
	using Tag = T;

	constexpr Result() = default;

	constexpr Result(const Value& v, bool b):
		value(&v),
		res(b)
	{}

	constexpr explicit operator bool () const { return res; }

	const Value* value = nullptr;
	bool res = false;
};

} // namespace Croissant