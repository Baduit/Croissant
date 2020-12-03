#pragma once

#include <Croissant/Result.hpp>
#include <Croissant/Value.hpp>
#include <Croissant/UsefulConcepts.hpp>

namespace Croissant
{

/*
** Croissant Value
*/
template <typename T, std::totally_ordered_with<T> U>
constexpr auto operator<(const Value<T>& t, const Value<U>& u)
{
    return Result<LessTag, U>(u.value, t.value < u.value);
}

template <NotValueNorResult U, std::totally_ordered_with<U> T>
constexpr auto operator<(const Value<T>& t, const U& u)
{
    return Result<LessTag, U>(u, t.value < u);
}

template <NotValueNorResult T, std::totally_ordered_with<T> U> 
constexpr auto operator<(const T& t, const Value<U>& u)
{
    return Result<LessTag, U>(u.value, t < u.value);
}

/*
** Result
*/
// Note : Result can only be on the left and it is done on purpose, it is not lazyness. If you have a result on the right you are misusing it
template <typename Left, NotValueOrderedWith<Left> Right> 
constexpr auto operator<(const Result<LessTag, Left>& left, const Right& right) -> Result<LessTag, Right>
{
    if (left)
        return Result<LessTag, Right>(right, *(left.value) < right);
    else
        return {};
}

template <typename Left, OrderedCroissantWith<Left> Right> 
constexpr auto operator<(const Result<LessTag, Left>& left, const Right& right) -> Result<LessTag, Right>
{
    if (left)
        return Result<LessTag, Right>(right, *(left.value) < right.value);
    else
        return {};
}

} // namespace Croissant
