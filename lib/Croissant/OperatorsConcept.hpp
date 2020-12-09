#pragma once

#include <concepts>

namespace Croissant
{

template <typename T>
concept NumberBuiltin = std::integral<T> || std::floating_point<T>;

/*
** Diff
*/

template <typename T, typename U>
concept DiffCompatible =
	requires(T t, U u)
	{
		{ t != u };
	};

/*
** Arithmetic operators
*/
template <typename T, typename U>
concept AddCompatible =
	requires(T t, U u)
	{
		{ t + u };
	};

template <typename T, typename U>
concept LessCompatible =
	requires(T t, U u)
	{
		{ t - u };
	};

template <typename T, typename U>
concept MultiplyCompatible =
	requires(T t, U u)
	{
		{ t * u };
	};

template <typename T, typename U>
concept DivideCompatible =
	requires(T t, U u)
	{
		{ t / u };
	};

template <typename T, typename U>
concept ModuloCompatible =
	requires(T t, U u)
	{
		{ t % u };
	};

template <typename T>
concept NegateCompatible =
	requires(T t)
	{
		{ -t };
	};

/*
** Arithmetic assigment operators
*/
template <typename T, typename U>
concept AddAssigmentCompatible =
	requires(T t, U u)
	{
		{ t += u };
	};

template <typename T, typename U>
concept LessAssigmentCompatible =
	requires(T t, U u)
	{
		{ t -= u };
	};

template <typename T, typename U>
concept MultiplyAssigmentCompatible =
	requires(T t, U u)
	{
		{ t *= u };
	};

template <typename T, typename U>
concept DivideAssigmentCompatible =
	requires(T t, U u)
	{
		{ t /= u };
	};

template <typename T, typename U>
concept ModuloAssigmentCompatible =
	requires(T t, U u)
	{
		{ t %= u };
	};

/*
** Bitwise operators
*/
template <typename T, typename U>
concept BitAndCompatible =
	requires(T t, U u)
	{
		{ t & u };
	};

template <typename T, typename U>
concept BitOrCompatible =
	requires(T t, U u)
	{
		{ t | u };
	};

template <typename T, typename U>
concept BitXorCompatible =
	requires(T t, U u)
	{
		{ t ^ u };
	};	

template <typename T>
concept BitNotCompatible =
	requires(T t)
	{
		{ ~t };
	};

/*
** Bitwise assigment operators
*/
template <typename T, typename U>
concept BitAndAssigmentCompatible =
	requires(T t, U u)
	{
		{ t &= u };
	};

template <typename T, typename U>
concept BitOrAssigmentCompatible =
	requires(T t, U u)
	{
		{ t |= u };
	};

template <typename T, typename U>
concept BitXorAssigmentCompatible =
	requires(T t, U u)
	{
		{ t ^= u };
	};	

/*
** Logical operators
*/		
template <typename T, typename U>
concept LogicAndCompatible =
	requires(T t, U u)
	{
		{ t && u };
	};

template <typename T, typename U>
concept LogicOrCompatible =
	requires(T t, U u)
	{
		{ t || u };
	};	

template <typename T>
concept LogicNotCompatible =
	requires(T t)
	{
		{ !t };
	};	

/*
** Shift operators
*/
template <typename T, typename U>
concept ShiftRightCompatible =
	requires(T t, U u)
	{
		{ t >> u };
	};

template <typename T, typename U>
concept ShiftLeftCompatible =
	requires(T t, U u)
	{
		{ t << u };
	};	

/*
** Shift assigment operators
*/
template <typename T, typename U>
concept ShiftRightAssigmentCompatible =
	requires(T t, U u)
	{
		{ t >>= u };
	};

template <typename T, typename U>
concept ShiftLeftAssigmentCompatible =
	requires(T t, U u)
	{
		{ t <<= u };
	};

} // namespace Croissant
