set_project("mos")
set_version("0.0.1")
set_xmakever("2.8.1")

add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {outputdir = "."})

add_requires({"fuse", system = true})

target("mos")
    set_kind("binary")
    set_languages("c++17")
    add_cxxflags("-D_FILE_OFFSET_BITS=64")
    add_files("src/*.cpp")
    add_packages("fuse")