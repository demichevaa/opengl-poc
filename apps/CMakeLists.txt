add_executable(opengl-poc-app
        game.c
        game.h
        level.h
        level.c
        block.h
        block.c
        ui.c
        ui.h
        main.c
        platform.c
        platform.h
        ball.c
        ball.h
)
target_link_libraries(opengl-poc-app ${GLIB_LIBRARIES} glad glfw opengl-poc-lib)
