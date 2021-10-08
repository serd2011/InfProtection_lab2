workspace "Lab2"
    configurations { 
        "Debug",
        "Release"
    }  
    configurations { "Debug", "Release" }

    platforms { "x86", "x86_64" }

    startproject "EncryptorApp"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["Encryptor"] = "%{wks.location}/Encryptor/include" 

include "Encryptor/"
include "EncryptorApp/"

