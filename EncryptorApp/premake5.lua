project "EncryptorApp"
    kind "WindowedApp"
    language "C++"
    characterset ("Unicode")

    links { "Encryptor" }

    targetdir ("%{wks.location}/build/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/build/obj/" .. outputdir .. "/%{prj.name}")

    files { 
        "**.h",
        "**.cpp",
    }

    includedirs{
        "%{IncludeDir.Encryptor}",
        "./"
    }

    pchheader "pch.h"
    pchsource "GUI/pch.cpp"

    filter "files:Utils/**.*"
        flags { 'NoPCH' }        
    
    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"

    filter "action:vs*"
        buildoptions {"/utf-8"}
        defines {"__COMPILER_VISUAL_C__"}
