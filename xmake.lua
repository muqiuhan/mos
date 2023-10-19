add_rules("mode.debug", "mode.release")

target("mos")
    set_kind("binary")
    add_cflags("-D_FILE_OFFSET_BITS=64")
    add_files("src/*.c")