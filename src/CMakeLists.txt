add_library(opengl-poc-lib assets.c
        assets.h
        ${PROJECT_SOURCE_DIR}/lib/stb_include/stb_implementation.c
        sprite.c
        shader.c
        texture.c
        texture.h
        shader.h
        sprite.h
        window.h
        window.c
        render.h
        debug.h
        debug.c
        viewport.c
        viewport.h
        palette.h
        collections.c
        collections.h
        render.c
        common.c
        common.h
        common.c
) # Add other source files as needed
target_include_directories(
        opengl-poc-lib
        PUBLIC ../include
        "${PROJECT_SOURCE_DIR}/lib/glad/include"
        "${PROJECT_SOURCE_DIR}/lib/glfw3/include"
        "${PROJECT_SOURCE_DIR}/lib/cglm/include"
)
target_link_libraries(opengl-poc-lib glad ${GLIB_LIBRARIES} glfw cglm_headers)
