#pragma once

#include <cstdint>
#include <string_view>
#include <string>
#include <iostream>
#include <cassert>

#include <Croissant/DisableWarning.hpp>
#include <Croissant/EqualityComparison.hpp>
#include <Croissant/MoreComparison.hpp>
#include <Croissant/MoreOrEqualComparison.hpp>
#include <Croissant/LessComparison.hpp>
#include <Croissant/LessOrEqualComparison.hpp>

namespace Croissant
{
/*
** Aliases
*/

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

inline Int operator"" _i(unsigned long long i)
{
	assert(static_cast<unsigned long long>(std::numeric_limits<int>::max()) >= i);
	return Int(static_cast<int>(i));
}

inline constexpr UInt operator"" _ui(unsigned long long i)
{
	assert(static_cast<unsigned long long>(std::numeric_limits<unsigned int>::max()) >= i);
	return UInt(static_cast<unsigned int>(i));
}


inline constexpr Int8 operator"" _i8(unsigned long long i)
{
	assert(static_cast<unsigned long long>(std::numeric_limits<int8_t>::max()) >= i);
	return Int8(static_cast<int8_t>(i));
}

inline constexpr UInt8 operator"" _ui8(unsigned long long i)
{
	assert(static_cast<unsigned long long>(std::numeric_limits<uint8_t>::max()) >= i);
	return UInt8(static_cast<uint8_t>(i));
}


inline constexpr Int16 operator"" _i16(unsigned long long i)
{
	assert(static_cast<unsigned long long>(std::numeric_limits<int16_t>::max()) >= i);
	return Int16(static_cast<int16_t>(i));
}

inline constexpr UInt16 operator"" _ui16(unsigned long long i)
{
	assert(static_cast<unsigned long long>(std::numeric_limits<uint16_t>::max()) >= i);
	return UInt16(static_cast<uint16_t>(i));
}


inline constexpr Int32 operator"" _i32(unsigned long long i)
{
	assert(static_cast<unsigned long long>(std::numeric_limits<int32_t>::max()) >= i);
	return Int32(static_cast<int32_t>(i));
}

inline constexpr UInt32 operator"" _ui32(unsigned long long i)
{
	assert(static_cast<unsigned long long>(std::numeric_limits<uint32_t>::max()) >= i);
	return UInt32(static_cast<uint32_t>(i));
}


inline constexpr Int64 operator"" _i64(unsigned long long i)
{
	assert(static_cast<unsigned long long>(std::numeric_limits<int64_t>::max()) >= i);
	return Int64(static_cast<int64_t>(i));
}

inline constexpr UInt64 operator"" _ui64(unsigned long long i)
{
	assert(static_cast<unsigned long long>(std::numeric_limits<uint64_t>::max()) >= i);
	return UInt64(static_cast<uint64_t>(i));
}

inline constexpr Size operator"" _size(unsigned long long i)
{
	assert(static_cast<unsigned long long>(std::numeric_limits<std::size_t>::max()) >= i);
	return Size(static_cast<std::size_t>(i));
}

} // IntegerLiterals

namespace FloatingPointLiterals
{

inline constexpr Float operator"" _f(long double d)
{
	assert(std::numeric_limits<float>::max() >= d);
	assert(std::numeric_limits<float>::lowest() <= d);
	return Float(static_cast<float>(d));
}

inline constexpr Double operator"" _d(long double d)
{
	assert(std::numeric_limits<double>::max() >= d);
	assert(std::numeric_limits<double>::lowest() <= d);
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
