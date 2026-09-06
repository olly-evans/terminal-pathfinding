cmake_minimum_required(VERSION 3.15)
project(myapp LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_compile_options(-g -O0 -Wall -Wextra)

# Main executable.
file(GLOB SRC_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.c)

set(LIB_SRC_FILES ${SRC_FILES})
list(FILTER LIB_SRC_FILES EXCLUDE REGEX "main\\.c$")


if(WIN32)
    list(FILTER SRC_FILES EXCLUDE REGEX "terminal_unix\\.c$")
else()
    list(FILTER SRC_FILES EXCLUDE REGEX "terminal_win32\\.c$")
endif()

add_library(app_lib STATIC ${SRC_FILES})
target_include_directories(app_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)


add_executable(main src/main.c)
target_link_libraries(main PRIVATE app_lib)

if(WIN32)
    target_link_libraries(main PRIVATE kernel32)
else()
    set_target_properties(main PROPERTIES SUFFIX ".out")
endif()

enable_testing()
add_subdirectory(test)