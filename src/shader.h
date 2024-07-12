#ifndef OPENGL_POC_SRC_SHADER_H_
#define OPENGL_POC_SRC_SHADER_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <cglm/cglm.h>
#include "render.h"

typedef struct ShaderProgram {
        unsigned int id;
        const char *vertexSource;
        const char *fragmentSource;
        const char *geometrySource;
} ShaderProgram;

int shaderProgramInitialize(ShaderProgram *program,
                            const char *vertexSource,
                            const char *fragmentSource,
                            const char *geometrySource);
int shaderProgramCompile(const ShaderProgram *program);
int shaderProgramUse(const ShaderProgram *program);
int shaderProgramDelete(const ShaderProgram *program);

int shaderSetMat3(ShaderProgram *shader, const char *uniformName, mat3 *value);
int shaderSetMat4(ShaderProgram *shader, const char *uniformName, mat4 *value);
int shaderSetVec3f(ShaderProgram *shader, const char *uniformName, vec3 value);
int shaderSetVec4f(ShaderProgram *shader, const char *uniformName, vec4 value);
int shaderSetInt(const ShaderProgram *shader, const char *uniformName, int value);
int shaderSetFloat(const ShaderProgram *shader, const char *uniformName, float value);

#endif //OPENGL_POC_SRC_SHADER_H_
