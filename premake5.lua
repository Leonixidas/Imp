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

include "Imp/Libs/GLFW"

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
        "3rdParty/VLD"
    }

    links
    {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "Off"
        systemversion "latest"

        defines
        {
            "IMP_WINDOWS",
            "IMP_BUILD_DLL"
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
            "3rdParty/VLD"
        }

        links
        {
            "Imp"
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
