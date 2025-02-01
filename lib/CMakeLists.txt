#
# project definitions
#

cmake_minimum_required(VERSION 3.28)

project(gamelib
        VERSION 1.0.0
        DESCRIPTION "2d lightweight game library"
        LANGUAGES CXX
)

#
# configuration
#

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 23)
set_property(GLOBAL PROPERTY CXX_EXTENSIONS OFF)
set_property(GLOBAL PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
set_property(GLOBAL PROPERTY LINK_WHAT_YOU_USE TRUE)

# warnings / flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(warnings -Wall -Wextra -Wformat-nonliteral -Wundef -Wshadow -Wwrite-strings -Wfloat-equal -Wswitch-default -Wmissing-format-attribute -Wswitch-enum -Wmissing-noreturn -Wno-unused-parameter -Wno-unused)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(warnings ${warnings} -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wsuggest-attribute=malloc -Wsuggest-attribute=format -Wsuggest-attribute=cold)
    endif()
endif()

# try to use ccache, if available
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-ggdb -O0)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(DEF B_PRODUCTION_MODE=ON)
    add_compile_options(-Ofast -flto)
endif()

#
# libraries
#

find_package(PkgConfig)
pkg_search_module(SDL3 REQUIRED sdl3)

set(IMGUI_SRC
        contrib/imgui/imgui.cpp
        contrib/imgui/imgui_demo.cpp
        contrib/imgui/imgui_draw.cpp
        contrib/imgui/imgui_tables.cpp
        contrib/imgui/imgui_widgets.cpp
        contrib/imgui/backends/imgui_impl_sdl3.cpp
        contrib/imgui/backends/imgui_impl_sdlrenderer3.cpp
        contrib/ImGuiFileDialog/ImGuiFileDialog.cpp
)

# ignore warnings in imported files
set_source_files_properties(${IMGUI_SRC} PROPERTIES COMPILE_FLAGS "-w")

add_library(gamelib STATIC
        src/game.hh
        src/ui.cc
        src/ui.hh
)

target_include_directories(gamelib PUBLIC ${SDL3_INCLUDE_DIRS})
target_include_directories(gamelib PUBLIC )
target_compile_options(gamelib PRIVATE ${warnings})


# TODO
