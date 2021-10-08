project "Encryptor"
    kind "StaticLib"
    language "C++"

    targetdir ("%{wks.location}/build/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/build/obj/" .. outputdir .. "/%{prj.name}")

    files { 
        "**.cpp",
        "**.h"
    }
    
    includedirs{
        "include",
        "src"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
