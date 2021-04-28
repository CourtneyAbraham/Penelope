#pragma once

#ifdef PENELOPE_PLATFORM_WINDOWS
#	ifdef PENELOPE_BUILD_DLL
#		define PENELOPE_API __declspec(dllexport)
#	else
#		define PENELOPE_API __declspec(dllimport)
#	endif
#else
#	error Penelope only supports windows
#endif