#pragma once

#include <concepts>
#include <type_traits>

namespace Croissant
{

struct EqualityTag {};
struct LessTag {};
struct MoreTag {};

template <typename T>
concept ComparaisonTag = std::same_as<T, EqualityTag> || std::same_as<T, LessTag> || std::same_as<T, MoreTag>;


struct ResultTag {};
template <typename T>
concept NotResult = (!std::is_base_of<ResultTag, T>::value);


struct ValueTag {};

template <typename T>
concept IsValue = (std::is_base_of<ValueTag, T>::value);

template <typename T>
concept NotValue = (!IsValue<T>);

template <typename T>
concept NotValueNorResult = NotValue<T> && NotResult<T>;

} // namespace Croissant