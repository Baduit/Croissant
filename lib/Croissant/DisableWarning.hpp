#pragma once

#if defined(__GNUC__) || defined(__clang__)
	#define CROISSANT_WARNING_PUSH _Pragma("GCC diagnostic push")
	#define CROISSANT_DISABLE_PARENTHESES_WARNING _Pragma("GCC diagnostic ignored \"-Wparentheses\"")
	#define CROISSANT_WARNING_POP _Pragma("GCC diagnostic pop")
#else
	#define CROISSANT_WARNING_PUSH
	#define CROISSANT_DISABLE_PARENTHESES_WARNING
	#define CROISSANT_WARNING_POP
#endif
