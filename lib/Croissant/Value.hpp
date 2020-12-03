#pragma once

#include <iostream>
#include <compare>
#include <concepts>
#include <type_traits>

#include <Croissant/Result.hpp>
#include <Croissant/Tags.hpp>

template <typename T>
struct CroissantValue: public CroissantValueTag
{
    using ValueType = T;

    constexpr explicit CroissantValue(ValueType&& t):
        value(std::move(t))
    {}

    constexpr explicit CroissantValue(const ValueType& t):
        value(t)
    {}

    ValueType value;
};

