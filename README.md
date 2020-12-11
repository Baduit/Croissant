# Croissant
## Description
It is a C++20 header only library. It makes comparisons more intuitive by chaining it like this :
* `x == y == z`
* `5 < x <= 25`
* `x == y == 12`

But you can only chain comparisons of the same category (more explanation in the __Limitations__ part). I define 3 categories:
* Equality : __==__
* Less : __<__ and __<=__
* More : __>__ and __>=__

## Example
```Cpp
Croissant::Int x(3);
Croissant::Int y(4);
Croissant::Int z(4);
if ((y == z == 4) && ( 5 > x >= 1))
{
	std::cout << "z and y equal 4. x is between 1 and 5 (1 included)" << std::endl;
}
```


## Why ?
Sometimes I write stuff like the snippet below and even if it does not often happen I don't find it elegant.
```Cpp
if (5 < x && x < 25)
	; // do stuff
else if (y == x && x == 15)
	// do other stuff
```
Also I wanted to experiment to see if could find a synxtax I like better.

## Croissant::Value
The structure Value in the namespace Croissant is a simple class and defined like this:
```Cpp
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
```
It can be constructed or assigned the same way than the type it encapsulate, you can access the underlying value with the operator*() or the method get_value() and you can call the method of the underlying object with the operator->().

The complexity is in the way it handles the comparisons operators, but you don't need to understand how it is defined to used it, but it is shortly explained later in this readme.

# Basic types alias
There are some alias for most number types, string and string_view in the namespace Croissant:
```Cpp
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

using Float = Value<float>;
using Double = Value<double>;

using StringView = Value<std::string_view>;
using String = Value<std::string>;

```

## Defined literals
There are literals defined most numbers types, string and string_view in the namespace Croissant:

```Cpp
namespace IntegerLiterals
{

inline constexpr Int operator"" _i(unsigned long long i);
inline constexpr UInt operator"" _ui(unsigned long long i);


inline constexpr Int8 operator"" _i8(unsigned long long i);
inline constexpr UInt8 operator"" _ui8(unsigned long long i);


inline constexpr Int16 operator"" _i16(unsigned long long i);
inline constexpr UInt16 operator"" _ui16(unsigned long long i);


inline constexpr Int32 operator"" _i32(unsigned long long i);
inline constexpr UInt32 operator"" _ui32(unsigned long long i);


inline constexpr Int64 operator"" _i64(unsigned long long i);
inline constexpr UInt64 operator"" _ui64(unsigned long long i);

inline constexpr Size operator"" _size(unsigned long long i);

} // IntegerLiterals

namespace FloatingPointLiterals
{

inline constexpr Float operator"" _f(long double d);
inline constexpr Double operator"" _d(long double d);

} // FloatingPointLiterals

namespace StringLiterals
{

inline String operator"" _s(const char* str, std::size_t size);
inline constexpr StringView operator"" _sv(const char* str, std::size_t size);

} // StringLiterals

```
For the number literals, if the literal argument is too big for the targeted type (more than 255 for a uint8_t for example) it is checked with an assert, so it is checked only on debug build.

## How does it work ?
I made the comparison operators return an object containing a boolean with the result of the comparison and a pointer to the right value if needed and this object can itself be compared if it is of the left (I could also have done it if it was on the right but it did not seemed right to do it) and returned a similar object. If the result was already false it can skip the comparison and return a false result.

Also there is an explicit conversion operator to bool so it works in a condition.


## How to integrate it ?
It is a header only library, you can use it by:
- Use CMake and link against it : `target_link_libraries(your_target Croissant)` (It is defined as an INTERFACE library)
- Add in your project the single header __Croissant.hpp__ which is in the folder __single_header__
- Add the lib directory in your path and include <Croissant/Croissant.hpp>

## Limitations
* `x == y > 15` : does not work because it is not readable and error prone and my goal is to make less error prone. __==__ is not of the same type as __>__
* `15 > x < 12` : is not easy to read and __>__ and __<__ are not part of the same catergories.
* `5 > (x > 1)` : because the goal is to assemble comparison you instinctively have in your mind as only one instruction (like x is between 5 and 1, or x, y and same are the same) but if you use parenthèsis like this, it looks like these are separate comparisons.
* `x == 15 != z` : we don't really know if __z__ must be different from __15__ and from __x__ or if __z__ must be different from __15__ only.

## Why is it named "Croissant" ?
I wanted an appetizing name and as a French I can assure you that a croissant is the best thing to eat ever.

## Note
I use the concepts from the std __std::totally_ordered_with__ and __std::equality_comparable_with__ for simplicity.

## Things that would be nice to do
* Make something to be able to write stuff lile that : `x != y != 15` meaning that the 3 values must be different
* More tests
* Use specifics concepts instead of __std::totally_ordered_with__ and __std::equality_comparable_with__
* More examples
* Doc about how it works

