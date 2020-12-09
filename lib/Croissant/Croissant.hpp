#pragma once

#include <cstdint>
#include <string_view>
#include <string>

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
/* String operator"" _s(const char* str, std::size_t size)
{
    return String(str, size);
} */

namespace StringLiterals
{

inline String operator"" _s(const char* str, std::size_t size)
{
    return String(str, size);
}

inline consteval StringView operator"" _sv(const char* str, std::size_t size)
{
    return StringView(str, size);
}

}

} // namespace Croissant
