#pragma once

#include <Croissant/Result.hpp>
#include <Croissant/Value.hpp>

/*
** Croissant Value equality
*/
template <typename T, typename U> requires std::equality_comparable_with<T, U>
constexpr auto operator==(const CroissantValue<T>& t, const CroissantValue<U>& u)
{
    return Result<EqualityTag, U>(u.value, t.value == u.value);
}

template <NotCroissantNorResult U, std::equality_comparable_with<U> T>
constexpr auto operator==(const CroissantValue<T>& t, const U& u)
{
    return Result<EqualityTag, U>(u, t.value == u);
}

template <NotCroissantNorResult T, std::equality_comparable_with<T> U> 
constexpr auto operator==(const T& t, const CroissantValue<U>& u)
{
    return Result<EqualityTag, U>(u.value, t == u.value);
}

/*
** Result Equality
*/
template <typename T, typename U>
concept NotCroissantComparableWith = NotCroissant<T> && std::equality_comparable_with<T, U>;

// Note : Result can only be on the left and it is done on purpose, it is not lazyness. If you have a result on the right you are misusing it
template <typename Left, NotCroissantComparableWith<Left> Right> 
constexpr auto operator==(const Result<EqualityTag, Left>& left, const Right& right) -> Result<EqualityTag, Right>
{
    if (left)
        return Result<EqualityTag, Right>(right, *(left.value) == right);
    else
        return {};
}

template <typename T, typename U>
concept ComparableCroissantWith = IsCroissant<T> && std::equality_comparable_with<typename T::ValueType, U>;

template <typename Left, ComparableCroissantWith<Left> Right> 
constexpr auto operator==(const Result<EqualityTag, Left>& left, const Right& right) -> Result<EqualityTag, Right>
{
    if (left)
        return Result<EqualityTag, Right>(right, *(left.value) == right.value);
    else
        return {};
}
