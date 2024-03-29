workspace "Imp"
    configurations
    {
        "Debug",
        "Release"
    }

    platforms {"x64", "x86"}
    startproject "BubbleBobble"

    filter "platforms:x86"
        system "Windows"
        architecture "x86"

    filter "platforms:x64"
        system "Windows"
        architecture "x86_64"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Imp/Libs/GLFW/include"
IncludeDir["Glad"] = "Imp/Libs/Glad/include"
IncludeDir["glm"] = "Imp/Libs/glm"
IncludeDir["Imgui"] = "Imp/Libs/Imgui"
IncludeDir["stb_image"] = "Imp/Libs/stb_image"
IncludeDir["box2d"] = "Imp/Libs/box2d"
IncludeDir["spdlog"] = "Imp/Libs/spdlog/include"


LibDirs = {}
LibDirs["Win32"] = "3rdParty/VLD/lib/Win32"
LibDirs["Win64"] = "3rdParty/VLD/lib/Win64"

include "Imp/Libs/GLFW"
include "Imp/Libs/Glad"
include "Imp/Libs/imgui"
include "Imp/Libs/box2d"

project "Imp"
        location "Imp"
        kind "StaticLib"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "ImpPCH.h"
    pchsource "Imp/src/ImpPCH.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{IncludeDir.stb_image}/**.h",
        "%{IncludeDir.stb_image}/**.cpp",
        "%{prj.name}/Libs/glm/glm/**.hpp",
        "%{prj.name}/Libs/glm/glm/**.inl",

    }

    includedirs
    {
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.Imgui}",
		"%{IncludeDir.spdlog}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.box2d}/include",
        "%{IncludeDir.box2d}/src",
        "3rdParty/VLD/include"
    }

    links
    {
        "GLFW",
        "Glad",
        "Imgui",
        "Box2D",
        "opengl32.lib"
    }

    defines
    {
     "_CRT_SECURE_NO_WARNINGS"
	}

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "IMP_WINDOWS",
            "IMP_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "IMP_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "IMP_RELEASE"
        runtime "Release"
        optimize "on"

    filter "platforms:x64"
        libdirs
        {
            "%{LibDirs.Win64}"
        }

    filter "platforms:x86"
        libdirs
        {
            "%{LibDirs.Win32}"
        }


project "BubbleBobble"
        location "BubbleBobble"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        files
        {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }

        includedirs
        {
            "Imp/src",
            "3rdParty/VLD/include",
            "Imp/Libs",
            "%{IncludeDir.glm}",
            "%{IncludeDir.box2d}",
			"%{IncludeDir.spdlog}"
        }

        links
        {
            "Imp",
            "vld.lib"
        }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "IMP_WINDOWS"
        }

    filter "configurations:Debug"
        defines "IMP_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "IMP_RELEASE"
        runtime "Release"
        optimize "on"

    filter "platforms:x64"
        libdirs
        {
            "%{LibDirs.Win64}"
        }

    filter "platforms:x86"
        libdirs
        {
            "%{LibDirs.Win32}"
        }
