workspace "aoc-solutions"
    configurations { "debug", "release" }

project "2021"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    architecture "x86_64"
    targetdir "bin/%{cfg.buildcfg}"

    files {
        "2021/**.cpp"
    }

    includedirs { "2021" }

    filter "configurations:debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:release"
        defines { "NDEBUG" }
        optimize "On"

    -- GCC flags
    filter {
        "system:linux",
        "action:gmake2"
    }
        buildoptions {
            "-pedantic-errors",
        }

    filter {
        "configurations:debug",
        "system:linux",
        "action:gmake2"
    }
        buildoptions {
            "-g",
            "-Wall",
            "-Wextra",
            "-Wsign-conversion",
            "-Wshadow",
            "-Werror",
            "-Wno-error=unused-variable",
            "-Wno-error=unused-parameter",
            "-Weffc++",
            "-fsanitize=address,undefined"
        }
        linkoptions {
            "-fsanitize=address,undefined"
        }

    filter {
        "configurations:release",
        "system:linux",
        "action:gmake2"
    }
        buildoptions "-Ofast"
