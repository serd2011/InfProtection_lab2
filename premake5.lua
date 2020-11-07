workspace "EncryptorApp"
    configurations { 
        "Debug",
        "Release"
    }  
    configurations { "Debug", "Release" }

    platforms { "x86", "x86_64" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "EncryptorApp"
    kind "WindowedApp"
    language "C++"
    characterset ("Unicode")

    targetdir ("build/bin/" .. outputdir)
    objdir ("build/obj/" .. outputdir)

    files { 
        "src/**.h",
        "src/**.cpp"
    }

    includedirs {
        "src/"        
    }

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"

    filter "action:vs*"
        buildoptions {"/utf-8"}
