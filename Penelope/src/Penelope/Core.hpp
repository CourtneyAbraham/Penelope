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

#define BIT(x) (1 << x)