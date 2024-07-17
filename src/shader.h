#ifndef OPENGL_POC_SRC_SHADER_H_
#define OPENGL_POC_SRC_SHADER_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <cglm/cglm.h>
#include "render.h"

struct ShaderProgram {
        unsigned int id;
        const char *str_vertex_source;
        const char *str_fragment_source;
        const char *str_geometry_source;
        const char *str_vertex_source_path;
        const char *str_fragment_source_path;
        const char *str_geometry_source_path;
};

int shader_initialize(
        struct ShaderProgram *shader,
        const char *str_vertex_source,
        const char *str_fragment_source,
        const char *str_geometry_source
);
int shader_compile(struct ShaderProgram *p_shader);
int shader_use(struct ShaderProgram *p_shader);
int shader_delete_program(struct ShaderProgram *p_shader);

int shader_set_mat3(struct ShaderProgram *p_shader, const char *str_uniform_name, mat3 *value);
int shader_set_mat4(struct ShaderProgram *p_shader, const char *str_uniform_name, mat4 *value);
int shader_set_vec3f(struct ShaderProgram *p_shader, const char *str_uniform_name, vec3 value);
int shaderSetVec4f(struct ShaderProgram *p_shader, const char *str_uniform_name, vec4 value);
int shaderSetInt(struct ShaderProgram *p_shader, const char *str_uniform_name, int value);
int shaderSetFloat(struct ShaderProgram *p_shader, const char *str_uniform_name, float value);
int shaderSetVec2f(struct ShaderProgram *p_shader, const char *str_uniform_name, vec2 value);


#endif //OPENGL_POC_SRC_SHADER_H_
