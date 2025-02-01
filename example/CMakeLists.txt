#
# project definitions
#

cmake_minimum_required(VERSION 3.28)

project(game-example
        VERSION 1.0.0
        DESCRIPTION "gamelib usage example"
        LANGUAGES CXX
)
set(EXE example)
set(GAMELIB_DIR lib)  # TODO - replace by where you're putting the library

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

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-ggdb -O0)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(DEF B_PRODUCTION_MODE=ON)
    add_compile_options(-Ofast -flto)
endif()

# try to use ccache, if available
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()

#
# libraries
#

include(FetchContent)
FetchContent_Declare(
        battery-embed
        GIT_REPOSITORY https://github.com/batterycenter/embed.git
        GIT_TAG        v1.2.19
)
FetchContent_MakeAvailable(battery-embed)

add_subdirectory(${GAMELIB_DIR})

#
# executable
#

add_executable(${EXE}
        src/main.cc)

target_compile_options(${EXE} PRIVATE ${warnings})
target_include_directories(${EXE} SYSTEM PUBLIC . ${GAMELIB_DIR}/src)
target_link_libraries(${EXE} PRIVATE gamelib SDL3::SDL3)

# TODO - embed

#
# check for leaks
#

add_custom_target(leaks)
add_custom_command(TARGET leaks
        POST_BUILD
        COMMENT "Check for leaks using valgrind."
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        DEPENDS ${EXE}
        COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=${CMAKE_SOURCE_DIR}/valgrind.supp ./${EXE}
)

add_custom_target(leaks-test)
add_custom_command(TARGET leaks-test
        POST_BUILD
        COMMENT "Check for leaks using valgrind (tests)."
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        DEPENDS ${EXE}-tests
        COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=${CMAKE_SOURCE_DIR}/valgrind.supp ./${EXE}-tests
)

add_custom_target(leaks-gen-suppressions)
add_custom_command(TARGET leaks-gen-suppressions
        POST_BUILD
        COMMENT "Check for leaks using valgrind. See valgrind-gen.supp when finished."
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --gen-suppressions=all --log-file=${CMAKE_SOURCE_DIR}/valgrind-gen.supp --suppressions=${CMAKE_SOURCE_DIR}/valgrind.supp ./${EXE}
)

# installation

install(TARGETS ${EXE}
        RUNTIME DESTINATION bin)