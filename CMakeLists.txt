# Works with 3.14 and tested through 3.29
cmake_minimum_required(VERSION 3.14...3.29)

# Project name and a few useful settings. Other commands can pick up the results
project(
    opengl-poc
    VERSION 0.1
    DESCRIPTION "An example project with CMake"
    LANGUAGES C
)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # Let's nicely support folders in IDEs
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    set(CMAKE_C_STANDARD 23)
    set(CMAKE_C_STANDARD_REQUIRED True)


    # Testing only available if this is the main app
    # Note this needs to be done in the main CMakeLists
    # since it calls enable_testing, which must be in the
    # main CMakeLists.
    include(CTest)
endif()

# OpenGL
find_package(OpenGL REQUIRED)
set(OpenGL_GL_PREFERENCE LEGACY)

set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
add_subdirectory(${LIB_DIR}/glfw)

include_directories(
        ${OPENGL_INCLUDE_DIRS}
        ${LIB_DIR}/glad/include
        ${LIB_DIR}/glfw/include
)

add_library(glad OBJECT ${LIB_DIR}/glad/src/glad.c)


# FetchContent added in CMake 3.11, downloads during the configure step
# FetchContent_MakeAvailable was added in CMake 3.14; simpler usage
include(FetchContent)

# The compiled library code is here
# add_subdirectory(src)

# The executable code is here
add_subdirectory(apps)

# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME) AND BUILD_TESTING)
    add_subdirectory(tests)
endif()
