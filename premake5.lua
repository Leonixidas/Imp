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
IncludeDir["glm"] = "Imp/Libs/glm/glm"


LibDirs = {}
LibDirs["Win32"] = "3rdParty/VLD/lib/Win32"
LibDirs["Win64"] = "3rdParty/VLD/lib/Win64"

include "Imp/Libs/GLFW"
include "Imp/libs/Glad"

project "Imp"
    location "Imp"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "ImpPCH.h"
    pchsource "Imp/src/ImpPCH.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.glm}",
        "3rdParty/VLD/include"
    }

    links
    {
        "GLFW",
        "Glad",
        "opengl32.lib",
        "vld.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "Off"
        systemversion "latest"

        defines
        {
            "IMP_WINDOWS",
            "IMP_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/BubbleBobble")
        }

    filter "configurations:Debug"
        defines "IMP_DEBUG"
        buildoptions "/MDd"
        symbols "On"
        ignoredefaultlibraries 
        { 
            "MSVCRT",
            "LIBCMT",
            "LIBCMTD"
        }

    filter "configurations:Release"
        defines "IMP_RELEASE"
        buildoptions "/MD"
        optimize "On"
        ignoredefaultlibraries 
        { 
            "MSVCRTD",
            "LIBCMT",
            "LIBCMTD"
        }

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
            "3rdParty/VLD/include"
        }

        links
        {
            "Imp",
            "vld.lib"
        }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "Off"
        systemversion "latest"

        defines
        {
            "IMP_WINDOWS"
        }

    filter "configurations:Debug"
        defines "IMP_DEBUG"
        buildoptions "/MDd"
        symbols "On"
        ignoredefaultlibraries 
        { 
            "MSVCRT",
            "LIBCMT",
            "LIBCMTD"
        }

    filter "configurations:Release"
        defines "IMP_RELEASE"
        buildoptions "/MD"
        optimize "On"
        ignoredefaultlibraries 
        { 
            "MSVCRTD",
            "LIBCMT",
            "LIBCMTD"
        }

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