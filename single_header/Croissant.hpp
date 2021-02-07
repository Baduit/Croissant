#pragma once

#include <concepts>
#include <type_traits>
#include <utility>
#include <cassert>
#include <limits>
#include <cstdint>
#include <string>
#include <string_view>

#if defined(__GNUC__) || defined(__clang__)
	#define CROISSANT_WARNING_PUSH _Pragma("GCC diagnostic push")
	#define CROISSANT_DISABLE_PARENTHESES_WARNING _Pragma("GCC diagnostic ignored \"-Wparentheses\"")
	#define CROISSANT_WARNING_POP _Pragma("GCC diagnostic pop")
#else
	#define CROISSANT_WARNING_PUSH
	#define CROISSANT_DISABLE_PARENTHESES_WARNING
	#define CROISSANT_WARNING_POP
#endif

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

    constexpr Value() = default;

    constexpr Value(const Value&) = default;
    constexpr Value& operator=(const Value&) = default;

    constexpr Value(Value&&) = default;
    constexpr Value& operator=(Value&&) = default;

    template <typename... Args> requires ConstructibleFrom<T, Args...>
    constexpr explicit(Explicit) Value(Args&&... args):
        value(std::forward<Args>(args)...)
    {}

    template <typename U> requires AssignableFrom<T, U>
    constexpr Value& operator=(U&& other)
    {
        value = std::forward<U>(other);
        return *this;
    }

    constexpr T& operator*() { return value; }
    constexpr const T& operator*() const { return value; }

    constexpr T& get_value() { return value; }
    constexpr const T& get_value() const { return value; }

    constexpr T* operator->() { return &value; }
    constexpr const T* operator->() const { return &value; }


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


using Int = Value<int>;
using UInt = Value<unsigned int>;

using Int8 = Value<int8_t>;
using UInt8 = Value<uint8_t>;

using Int16 = Value<int16_t>;
using UInt16 = Value<uint16_t>;

using Int32 = Value<int32_t>;
using UInt32 = Value<uint32_t>;

using Int64 = Value<int64_t>;
using UInt64 = Value<uint64_t>;

using Size = Value<std::size_t>;
// Does not seems to be supported yet
//using SSize = Value<std::ssize_t>;

using Float = Value<float>;
using Double = Value<double>;

using StringView = Value<std::string_view>;
using String = Value<std::string>;

/*
** Literals
*/ 
namespace IntegerLiterals
{

inline constexpr Int operator"" _i(unsigned long long i)
{
    assert(static_cast<unsigned long long>(std::numeric_limits<int>::max()) <= i);
    return Int(static_cast<int>(i));
}

inline constexpr UInt operator"" _ui(unsigned long long i)
{
    assert(static_cast<unsigned long long>(std::numeric_limits<unsigned int>::max()) <= i);
    return UInt(static_cast<unsigned int>(i));
}


inline constexpr Int8 operator"" _i8(unsigned long long i)
{
    assert(static_cast<unsigned long long>(std::numeric_limits<int8_t>::max()) <= i);
    return Int8(static_cast<int8_t>(i));
}

inline constexpr UInt8 operator"" _ui8(unsigned long long i)
{
    assert(static_cast<unsigned long long>(std::numeric_limits<uint8_t>::max()) <= i);
    return UInt8(static_cast<uint8_t>(i));
}


inline constexpr Int16 operator"" _i16(unsigned long long i)
{
    assert(static_cast<unsigned long long>(std::numeric_limits<int16_t>::max()) <= i);
    return Int16(static_cast<int16_t>(i));
}

inline constexpr UInt16 operator"" _ui16(unsigned long long i)
{
    assert(static_cast<unsigned long long>(std::numeric_limits<uint16_t>::max()) <= i);
    return UInt16(static_cast<uint16_t>(i));
}


inline constexpr Int32 operator"" _i32(unsigned long long i)
{
    assert(static_cast<unsigned long long>(std::numeric_limits<int32_t>::max()) <= i);
    return Int32(static_cast<int32_t>(i));
}

inline constexpr UInt32 operator"" _ui32(unsigned long long i)
{
    assert(static_cast<unsigned long long>(std::numeric_limits<uint32_t>::max()) <= i);
    return UInt32(static_cast<uint32_t>(i));
}


inline constexpr Int64 operator"" _i64(unsigned long long i)
{
    assert(static_cast<unsigned long long>(std::numeric_limits<int64_t>::max()) <= i);
    return Int64(static_cast<int64_t>(i));
}

inline constexpr UInt64 operator"" _ui64(unsigned long long i)
{
    assert(static_cast<unsigned long long>(std::numeric_limits<uint64_t>::max()) <= i);
    return UInt64(static_cast<uint64_t>(i));
}

inline constexpr Size operator"" _size(unsigned long long i)
{
    assert(static_cast<unsigned long long>(std::numeric_limits<std::size_t>::max()) <= i);
    return Size(static_cast<std::size_t>(i));
}

} // IntegerLiterals

namespace FloatingPointLiterals
{

inline constexpr Float operator"" _f(long double d)
{
    assert(std::numeric_limits<float>::max() <= d);
    assert(std::numeric_limits<float>::lowest() >= d);
    return Float(static_cast<float>(d));
}

inline constexpr Double operator"" _d(long double d)
{
    assert(std::numeric_limits<double>::max() <= d);
    assert(std::numeric_limits<double>::lowest() >= d);
    return Double(static_cast<double>(d));
}

} // FloatingPointLiterals

namespace StringLiterals
{

inline String operator"" _s(const char* str, std::size_t size)
{
    return String(str, size);
}

inline constexpr StringView operator"" _sv(const char* str, std::size_t size)
{
    return StringView(str, size);
}

} // StringLiterals

} // namespace Croissant
