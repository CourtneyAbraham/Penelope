#pragma once

#ifdef PN_PLATFORM_WINDOWS
#	ifdef PN_BUILD_DLL
#		define PN_API __declspec(dllexport)
#	else
#		define PN_API __declspec(dllimport)
#	endif
#else
#	error Penelope only supports windows
#endif