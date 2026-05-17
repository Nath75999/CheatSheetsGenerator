cmake_minimum_required(VERSION 3.16)
project(CheatSheetsGenerator LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(ExternalProject)
find_program(MAKE_EXECUTABLE NAMES make gmake REQUIRED)

ExternalProject_Add(mupdf
    SOURCE_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/mupdf
    CONFIGURE_COMMAND ""
    BUILD_COMMAND     ${CMAKE_COMMAND} -E chdir <SOURCE_DIR>
                      ${MAKE_EXECUTABLE} -j 
                      build=release
                      libs
                      HAVE_FREETYPE=yes
    INSTALL_COMMAND   ""
    BUILD_IN_SOURCE   ON
    BUILD_ALWAYS      OFF
)

ExternalProject_Get_Property(mupdf SOURCE_DIR)
set(MUPDF_DIR ${SOURCE_DIR})

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.c")

add_executable(CSG ${SOURCES})

add_dependencies(CSG mupdf)

target_include_directories(CSG PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${MUPDF_DIR}/include
)

target_link_libraries(CSG PRIVATE
    ${MUPDF_DIR}/build/release/libmupdf.a
    ${MUPDF_DIR}/build/release/libmupdf-third.a
)

message(STATUS "MuPDF dir: ${MUPDF_DIR}")