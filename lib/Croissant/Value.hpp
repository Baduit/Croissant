#pragma once

#include <iostream>
#include <compare>
#include <concepts>
#include <type_traits>

#include <Croissant/Result.hpp>
#include <Croissant/Tags.hpp>

namespace Croissant
{

template <typename T, typename... Args>
concept ConstructibleFrom =
    requires (Args&&... args)
    {
        { T(std::forward<Args>(args)...) } -> std::same_as<T>;
    };

template <typename T, typename U>
concept AssignableFrom =
    requires (T t, U u)
    {
        { t = u };
    };

template <typename T, bool Explicit = false>
struct Value: public ValueTag
{
    using ValueType = T;

    Value() = default;

    Value(const Value&) = default;
    Value& operator=(const Value&) = default;

    Value(Value&&) = default;
    Value& operator=(Value&&) = default;

    template <typename... Args> requires ConstructibleFrom<T, Args...>
    constexpr explicit(Explicit) Value(Args&&... args):
        value(std::forward<Args>(args)...)
    {}

    template <typename U> requires AssignableFrom<T, U>
    Value& operator=(U&& other)
    {
        value = std::forward<U>(other);
        return *this;
    }

    T& operator*() { return value; }
    const T& operator*() const { return value; }

    T& get_value() { return value; }
    const T& get_value() const { return value; }

    T* operator->() { return &value; }
    const T* operator->() const { return &value; }


    ValueType value;
};

} // namespace Croissant

