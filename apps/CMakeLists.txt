## OpenGL
#find_package(OpenGL REQUIRED)
#set(OpenGL_GL_PREFERENCE LEGACY)
#
#include_directories(
#        ${OPENGL_INCLUDE_DIRS}
#        ${LIB_DIR}/glad/include
#        ${LIB_DIR}/glfw/include
#        ${LIB_DIR}/cmocka-1.1.7/include
#)
#
#add_library(glad OBJECT ${LIB_DIR}/glad/src/glad.c)

add_executable(opengl-poc-app main.c)
target_link_libraries(opengl-poc-app glad glfw)
