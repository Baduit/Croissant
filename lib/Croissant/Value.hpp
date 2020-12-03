#pragma once

#include <iostream>
#include <compare>
#include <concepts>
#include <type_traits>

#include <Croissant/Result.hpp>
#include <Croissant/Tags.hpp>

namespace Croissant
{

template <typename T>
struct Value: public ValueTag
{
    using ValueType = T;

    constexpr explicit Value(ValueType&& t):
        value(std::move(t))
    {}

    constexpr explicit Value(const ValueType& t):
        value(t)
    {}

    ValueType value;
};

} // namespace Croissant

