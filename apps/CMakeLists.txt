add_executable(opengl-poc-app main.c
        game.c)
target_link_libraries(opengl-poc-app ${GLIB_LIBRARIES} glad glfw opengl-poc-lib)
