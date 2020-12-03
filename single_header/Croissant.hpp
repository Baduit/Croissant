#pragma once

#include <concepts>
#include <type_traits>
#include <utility>

namespace Croissant
{

struct EqualityTag {};
struct LessTag {};
struct MoreTag {};

template <typename T>
concept ComparisonTag = std::same_as<T, EqualityTag> || std::same_as<T, LessTag> || std::same_as<T, MoreTag>;


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

template <typename T, typename U>
concept NotValueEqualityComparableWith = NotValue<T> && std::equality_comparable_with<T, U>;

template <typename T, typename U>
concept EqualityComparableCroissantWith = IsValue<T> && std::equality_comparable_with<typename T::ValueType, U>;

template <typename T, typename U>
concept NotValueOrderedWith = NotValue<T> && std::totally_ordered_with<T, U>;

template <typename T, typename U>
concept OrderedCroissantWith = IsValue<T> && std::totally_ordered_with<typename T::ValueType, U>;

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

template <ComparisonTag T, typename Value>
struct Result : public ResultTag
{
    using Tag = T;

    constexpr Result() = default;

    constexpr Result(const Value& v, bool b):
        value(&v),
        res(b)
    {}

    constexpr explicit operator bool () const { return res; }

    const Value* value = nullptr;
    bool res = false;
};

/*
** Croissant Value
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
** Result
*/
// Note : Result can only be on the left and it is done on purpose, it is not lazyness. If you have a result on the right you are misusing it
template <typename Left, NotValueEqualityComparableWith<Left> Right> 
constexpr auto operator==(const Result<EqualityTag, Left>& left, const Right& right) -> Result<EqualityTag, Right>
{
    if (left)
        return Result<EqualityTag, Right>(right, *(left.value) == right);
    else
        return {};
}

template <typename Left, EqualityComparableCroissantWith<Left> Right> 
constexpr auto operator==(const Result<EqualityTag, Left>& left, const Right& right) -> Result<EqualityTag, Right>
{
    if (left)
        return Result<EqualityTag, Right>(right, *(left.value) == right.value);
    else
        return {};
}

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

/*
** Croissant Value
*/
template <typename T, std::totally_ordered_with<T> U>
constexpr auto operator<=(const Value<T>& t, const Value<U>& u)
{
    return Result<LessTag, U>(u.value, t.value <= u.value);
}

template <NotValueNorResult U, std::totally_ordered_with<U> T>
constexpr auto operator<=(const Value<T>& t, const U& u)
{
    return Result<LessTag, U>(u, t.value <= u);
}

template <NotValueNorResult T, std::totally_ordered_with<T> U> 
constexpr auto operator<=(const T& t, const Value<U>& u)
{
    return Result<LessTag, U>(u.value, t <= u.value);
}

/*
** Result
*/
// Note : Result can only be on the left and it is done on purpose, it is not lazyness. If you have a result on the right you are misusing it
template <typename Left, NotValueOrderedWith<Left> Right> 
constexpr auto operator<=(const Result<LessTag, Left>& left, const Right& right) -> Result<LessTag, Right>
{
    if (left)
        return Result<LessTag, Right>(right, *(left.value) <= right);
    else
        return {};
}

template <typename Left, OrderedCroissantWith<Left> Right> 
constexpr auto operator<=(const Result<LessTag, Left>& left, const Right& right) -> Result<LessTag, Right>
{
    if (left)
        return Result<LessTag, Right>(right, *(left.value) <= right.value);
    else
        return {};
}

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

/*
** Croissant Value
*/
template <typename T, std::totally_ordered_with<T> U>
constexpr auto operator>=(const Value<T>& t, const Value<U>& u)
{
    return Result<MoreTag, U>(u.value, t.value >= u.value);
}

template <NotValueNorResult U, std::totally_ordered_with<U> T>
constexpr auto operator>=(const Value<T>& t, const U& u)
{
    return Result<MoreTag, U>(u, t.value >= u);
}

template <NotValueNorResult T, std::totally_ordered_with<T> U> 
constexpr auto operator>=(const T& t, const Value<U>& u)
{
    return Result<MoreTag, U>(u.value, t >= u.value);
}

/*
** Result
*/
// Note : Result can only be on the left and it is done on purpose, it is not lazyness. If you have a result on the right you are misusing it
template <typename Left, NotValueOrderedWith<Left> Right> 
constexpr auto operator>=(const Result<MoreTag, Left>& left, const Right& right) -> Result<MoreTag, Right>
{
    if (left)
        return Result<MoreTag, Right>(right, *(left.value) >= right);
    else
        return {};
}

template <typename Left, OrderedCroissantWith<Left> Right> 
constexpr auto operator>=(const Result<MoreTag, Left>& left, const Right& right) -> Result<MoreTag, Right>
{
    if (left)
        return Result<MoreTag, Right>(right, *(left.value) >= right.value);
    else
        return {};
}

} // namespace Croissant
