#include "shader.h"

void shaderHandleErrors(const ShaderProgram *p_shaderProgram, int type, unsigned int shader);
void shaderProgramHandleErrors(const ShaderProgram *p_shaderProgram);

int shaderProgramInitialize(
    ShaderProgram *program,
    const char *vertexSource,
    const char *fragmentSource,
    const char *geometrySource
) {
        program->vertexSource = vertexSource;
        program->fragmentSource = fragmentSource;
        program->geometrySource = geometrySource;
        program->id = glCreateProgram();

        return EXIT_SUCCESS;
}

int shaderProgramUse(const ShaderProgram *program) {
        glUseProgram(program->id);

        return EXIT_SUCCESS;
}

int shaderProgramDelete(const ShaderProgram *program) {
        glDeleteProgram(program->id);

        return EXIT_SUCCESS;
}

int shaderProgramCompile(const ShaderProgram *program) {
        unsigned int sVertex, sFragment, sGeometry;
        bool hasGeometry = program->geometrySource != NULL;


        if (hasGeometry) {
                sGeometry = glCreateShader(GL_GEOMETRY_SHADER);
                glShaderSource(sGeometry, 1, &program->geometrySource, NULL);
                glCompileShader(sGeometry);
                shaderHandleErrors(program, 3,sGeometry);

                glAttachShader(program->id, sGeometry);
        }

        sVertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(sVertex, 1, &program->vertexSource, NULL);
        glCompileShader(sVertex);
        shaderHandleErrors(program, 1, sVertex);
        glAttachShader(program->id, sVertex);


        sFragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(sFragment, 1, &program->fragmentSource, NULL);
        glCompileShader(sFragment);
        shaderHandleErrors(program, 2,sFragment);
        glAttachShader(program->id, sFragment);

        glLinkProgram(program->id);

        shaderProgramHandleErrors(program);

        glDeleteShader(sVertex);
        glDeleteShader(sFragment);

        if (hasGeometry) {
                glDeleteShader(sGeometry);
        }

        return EXIT_SUCCESS;
}

void shaderHandleErrors(const ShaderProgram *p_shaderProgram, int type, unsigned int shader) {
        int success;
        char infoLog[1024];

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);

                const char *source;
                switch (type) {
                        case 1:
                                source = p_shaderProgram->vertexSource;
                                break;
                        case 2:
                                source = p_shaderProgram->fragmentSource;
                                break;
                        case 3:
                                source = p_shaderProgram->geometrySource;
                                break;
                        default:
                                break;
                }
                fprintf(stderr, "[SHADER] -> Compile error\nInfo Log:\n%s\nSource:\n%s\n", infoLog, source);
                exit(EXIT_FAILURE);
        }
}
void shaderProgramHandleErrors(const ShaderProgram *p_shaderProgram) {
        int success;
        char infoLog[1024];

        glGetProgramiv(p_shaderProgram->id, GL_LINK_STATUS, &success);

        if (!success) {
                glGetProgramInfoLog(p_shaderProgram->id, 1024, NULL, infoLog);
                fprintf(stderr, "[SHADER] -> Linking error:\n%s", infoLog);
                exit(EXIT_FAILURE);
        }
}

int uniformGetLocation(int *location,
                       const ShaderProgram *shader,
                       const char *uniformName) {
        *location = (int)glGetUniformLocation(shader->id, uniformName);
        if (*location == -1) {
                fprintf(stderr,
                        "[SHADER:UNIFORM] -> Uniform parameter `%s` not found:\n%s\n%s\n%s\n",
                        uniformName, shader->vertexSourcePath, shader->fragmentSourcePath, shader->geometrySourcePath);
                exit(EXIT_FAILURE);
        }

        return EXIT_SUCCESS;
}

int shaderSetMat3(ShaderProgram *shader, const char *uniformName, mat3 *value) {
        int location;
        uniformGetLocation(&location, shader, uniformName);

        glUniformMatrix3fv(location, 1, GL_FALSE, (const GLfloat *)value);

        return EXIT_SUCCESS;
}


int shaderSetMat4(ShaderProgram *shader, const char *uniformName, mat4 *value) {
        int location;
        uniformGetLocation(&location, shader, uniformName);

        glUniformMatrix4fv(location, 1, GL_FALSE, (const GLfloat *)value);

        return EXIT_SUCCESS;
}

int shaderSetVec3f(ShaderProgram *shader, const char *uniformName, vec3 value) {
        int location;
        uniformGetLocation(&location, shader, uniformName);

        glUniform3f(location, value[0], value[1], value[2]);

        return EXIT_SUCCESS;
}

int shaderSetVec4f(ShaderProgram *shader, const char *uniformName, vec4 value) {
        int location;
        uniformGetLocation(&location, shader, uniformName);

        glUniform4f(location, value[0], value[1], value[2], value[3]);

        return EXIT_SUCCESS;
}

int shaderSetVec2f(ShaderProgram *shader, const char *uniformName, vec2 value) {
        int location;
        uniformGetLocation(&location, shader, uniformName);

        glUniform2f(location, value[0], value[1]);

        return EXIT_SUCCESS;
}

int shaderSetFloat(const ShaderProgram *shader, const char *uniformName, float value) {
        int location;
        uniformGetLocation(&location, shader, uniformName);

        glUniform1f(location, value);

        return EXIT_SUCCESS;
}

int shaderSetInt(const ShaderProgram *shader, const char *uniformName, int value) {
        int location;
        uniformGetLocation(&location, shader, uniformName);

        glUniform1i(location, value);

        return EXIT_SUCCESS;
}