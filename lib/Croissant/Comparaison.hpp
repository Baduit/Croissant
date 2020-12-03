#pragma once

#include <Croissant/Result.hpp>
#include <Croissant/Value.hpp>

namespace Croissant
{

/*
** Croissant Value equality
*/
template <typename T, std::equality_comparable_with<T> U>
constexpr auto operator==(const Value<T>& t, const Value<U>& u)
{
    return Result<EqualityTag, U>(u.value, t.value == u.value);
}

template <NotValueNorResult U, std::equality_comparable_with<U> T>
constexpr auto operator==(const Value<T>& t, const U& u)
{
    return Result<EqualityTag, U>(u, t.value == u);
}

template <NotValueNorResult T, std::equality_comparable_with<T> U> 
constexpr auto operator==(const T& t, const Value<U>& u)
{
    return Result<EqualityTag, U>(u.value, t == u.value);
}

/*
** Result Equality
*/
template <typename T, typename U>
concept NotValueComparableWith = NotValue<T> && std::equality_comparable_with<T, U>;

// Note : Result can only be on the left and it is done on purpose, it is not lazyness. If you have a result on the right you are misusing it
template <typename Left, NotValueComparableWith<Left> Right> 
constexpr auto operator==(const Result<EqualityTag, Left>& left, const Right& right) -> Result<EqualityTag, Right>
{
    if (left)
        return Result<EqualityTag, Right>(right, *(left.value) == right);
    else
        return {};
}

template <typename T, typename U>
concept ComparableCroissantWith = IsValue<T> && std::equality_comparable_with<typename T::ValueType, U>;

template <typename Left, ComparableCroissantWith<Left> Right> 
constexpr auto operator==(const Result<EqualityTag, Left>& left, const Right& right) -> Result<EqualityTag, Right>
{
    if (left)
        return Result<EqualityTag, Right>(right, *(left.value) == right.value);
    else
        return {};
}

} // namespace Croissant