#pragma once

#include <Croissant/Result.hpp>
#include <Croissant/Number.hpp>
#include <Croissant/UsefulConcepts.hpp>

namespace Croissant
{

/*
** Croissant Value
*/
template <typename T, std::totally_ordered_with<T> U>
constexpr auto operator>(const Value<T>& t, const Value<U>& u)
{
	return Result<MoreTag, U>(u.value, t.value > u.value);
}

template <NotValueNorResult U, std::totally_ordered_with<U> T>
constexpr auto operator>(const Value<T>& t, const U& u)
{
	return Result<MoreTag, U>(u, t.value > u);
}

template <NotValueNorResult T, std::totally_ordered_with<T> U> 
constexpr auto operator>(const T& t, const Value<U>& u)
{
	return Result<MoreTag, U>(u.value, t > u.value);
}

/*
** Result
*/
// Note : Result can only be on the left and it is done on purpose, it is not lazyness. If you have a result on the right you are misusing it
template <typename Left, NotValueOrderedWith<Left> Right> 
constexpr auto operator>(const Result<MoreTag, Left>& left, const Right& right) -> Result<MoreTag, Right>
{
	if (left)
		return Result<MoreTag, Right>(right, *(left.value) > right);
	else
		return {};
}

template <typename Left, OrderedCroissantWith<Left> Right> 
constexpr auto operator>(const Result<MoreTag, Left>& left, const Right& right) -> Result<MoreTag, Right>
{
	if (left)
		return Result<MoreTag, Right>(right, *(left.value) > right.value);
	else
		return {};
}

} // namespace Croissant
