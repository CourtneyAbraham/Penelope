workspace "Penelope"
	architecture "x64"
	configurations {
		"Debug",
		"Release",
		"Dist"
	}
	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Penelope/vendor/GLFW/include"

include "Penelope/vendor/GLFW"

project "Penelope"
	location "Penelope"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pnpch.hpp"
	pchsource "%{prj.name}/src/pnpch.cpp"

	files {
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.c"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links {
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"PN_PLATFORM_WINDOWS",
			"PN_BUILD_DLL"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .."/Sandbox")
		}
		
	filter "configurations:Debug"
		defines {
			"PN_DEBUG",
			"PN_ENABLE_ASSERTS"
		}
		symbols "On"
	filter "configurations:Release"
		defines "PN_RELEASE"
		optimize "On"
	filter "configurations:Dist"
		defines "PN_DIST"
		symbols "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.c"
	}
	
	includedirs {
		"Penelope/vendor/spdlog/include",
		"Penelope/src"
	}

	links {
		"Penelope"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"PN_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines {
			"PN_DEBUG",
			"PN_ENABLE_ASSERTS"
		}
		symbols "On"
	filter "configurations:Release"
		defines "PN_RELEASE"
		optimize "On"
	filter "configurations:Dist"
		defines "PN_DIST"
		symbols "On"
