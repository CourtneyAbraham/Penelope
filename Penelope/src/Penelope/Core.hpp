#pragma once

#ifdef PN_PLATFORM_WINDOWS
#	ifdef PN_BUILD_DLL
#		define PENELOPE_API __declspec(dllexport)
#	else
#		define PENELOPE_API __declspec(dllimport)
#	endif
#else
#	error Penelope only supports windows
#endif

#ifdef PN_ENABLE_ASSERTS
#	define PN_ASSERT(x, ...) {if (!(x)) {PN_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak; } }
#	define PN_CORE_ASSERT(x, ...) {if (!(x)) {PN_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak; } }
#else
#	define PN_ASSERT(x, ...)
#	define PN_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)