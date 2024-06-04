cmake_minimum_required(VERSION 3.28)
project(opengl-poc C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

# OpenGL
find_package(OpenGL REQUIRED)
set(OpenGL_GL_PREFERENCE LEGACY)


# libs
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
add_subdirectory(${LIB_DIR}/glfw)

include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${LIB_DIR}/glad/include
    ${LIB_DIR}/glfw/include
)

add_library(glad OBJECT ${LIB_DIR}/glad/src/glad.c)

add_executable(opengl-poc src/main.c)
target_link_libraries(opengl-poc glad glfw)
