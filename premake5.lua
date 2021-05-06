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
IncludeDir["Glad"] = "Penelope/vendor/Glad/include"
IncludeDir["ImGui"] = "Penelope/vendor/ImGui"
IncludeDir["glm"] = "Penelope/vendor/ImGui"

group "Dependencies"

	include "Penelope/vendor/GLFW"
	include "Penelope/vendor/Glad"
	include "Penelope/vendor/ImGui"

group ""

project "Penelope"
	location "Penelope"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	
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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}
	
	defines "_CRT_SECURE_NO_WARNINGS"

	filter "system:windows"
		systemversion "latest"

		defines {
			"PN_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines {
			"PN_DEBUG",
			"PN_ENABLE_ASSERTS"
		}
		runtime "Debug"
		symbols "On"
	filter "configurations:Release"
		defines "PN_RELEASE"
		runtime "Release"
		optimize "On"
	filter "configurations:Dist"
		defines "PN_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	
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
		"Penelope/src",
		"Penelope/vendor"
	}

	links {
		"Penelope"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"PN_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines {
			"PN_DEBUG",
			"PN_ENABLE_ASSERTS"
		}
		runtime "Debug"
		symbols "On"
	filter "configurations:Release"
		defines "PN_RELEASE"
		runtime "Release"
		optimize "On"
	filter "configurations:Dist"
		defines "PN_DIST"
		runtime "Release"
		optimize "On"
