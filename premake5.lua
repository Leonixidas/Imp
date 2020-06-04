workspace "Imp"
    configurations
    {
        "Debug",
        "Release"
    }

    platforms {"x64", "x86"}

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



LibDirs = {}
LibDirs["Win32"] = "3rdParty/VLD/lib/Win32"
LibDirs["Win64"] = "3rdParty/VLD/lib/Win64"

include "Imp/Libs/GLFW"
include "Imp/Libs/Glad"
include "Imp/Libs/imgui"

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
        "%{prj.name}/src/**.cpp".
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
        "3rdParty/VLD/include"
    }

    links
    {
        "GLFW",
        "Glad",
        "Imgui",
        "opengl32.lib"
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
            "%{IncludeDir.glm}"
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