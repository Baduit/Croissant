#pragma once

#include <concepts>
#include <type_traits>

#include <Croissant/Tags.hpp>

namespace Croissant
{

template <typename T, typename U>
concept NotValueEqualityComparableWith = NotValue<T> && std::equality_comparable_with<T, U>;

template <typename T, typename U>
concept EqualityComparableCroissantWith = IsValue<T> && std::equality_comparable_with<typename T::ValueType, U>;

template <typename T, typename U>
concept NotValueOrderedWith = NotValue<T> && std::totally_ordered_with<T, U>;

template <typename T, typename U>
concept OrderedCroissantWith = IsValue<T> && std::totally_ordered_with<typename T::ValueType, U>;


} // namespace Croissant
