import os

env = SConscript("extern/godot-cpp/SConstruct")

env.Append(CPPPATH=["src/core", "src/gdextension"])

sources = Glob("src/core/*.cpp") + Glob("src/gdextension/*.cpp")

library = env.SharedLibrary(
    target="client/bin/maze_engine" + env["suffix"] + env["SHLIBSUFFIX"],
    source=sources
)

Default(library)