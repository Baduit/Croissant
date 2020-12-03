#pragma once

#include <concepts>
#include <type_traits>

struct EqualityTag {};
struct LessTag {};
struct MoreTag {};

template <typename T>
concept ComparaisonTag = std::same_as<T, EqualityTag> || std::same_as<T, LessTag> || std::same_as<T, MoreTag>;


struct ResultTag {};
template <typename T>
concept NotResult = (!std::is_base_of<ResultTag, T>::value);


struct CroissantValueTag {};

template <typename T>
concept IsCroissant = (std::is_base_of<CroissantValueTag, T>::value);

template <typename T>
concept NotCroissant = (!IsCroissant<T>);

template <typename T>
concept NotCroissantNorResult = NotCroissant<T> && NotResult<T>;