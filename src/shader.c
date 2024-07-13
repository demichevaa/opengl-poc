#include "shader.h"

void shaderHandleErrors(unsigned int shader);
void shaderProgramHandleErrors(unsigned int program);

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
                shaderHandleErrors(sGeometry);

                glAttachShader(program->id, sGeometry);
        }

        sVertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(sVertex, 1, &program->vertexSource, NULL);
        glCompileShader(sVertex);
        shaderHandleErrors(sVertex);
        glAttachShader(program->id, sVertex);


        sFragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(sFragment, 1, &program->fragmentSource, NULL);
        glCompileShader(sFragment);
        shaderHandleErrors(sFragment);
        glAttachShader(program->id, sFragment);

        glLinkProgram(program->id);

        shaderProgramHandleErrors(program->id);

        glDeleteShader(sVertex);
        glDeleteShader(sFragment);

        if (hasGeometry) {
                glDeleteShader(sGeometry);
        }

        return EXIT_SUCCESS;
}

void shaderHandleErrors(unsigned int shader) {
        int success;
        char infoLog[1024];

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                fprintf(stderr, "ERROR::Shader::Compile:\n%s", infoLog);
                exit(EXIT_FAILURE);
        }
}
void shaderProgramHandleErrors(unsigned int program) {
        int success;
        char infoLog[1024];

        glGetProgramiv(program, GL_LINK_STATUS, &success);

        if (!success) {
                glGetProgramInfoLog(program, 1024, NULL, infoLog);
                fprintf(stderr, "ERROR::Shader::Linking:\n%s", infoLog);
                exit(EXIT_FAILURE);
        }
}

int uniformGetLocation(int *location,
                       const ShaderProgram *shader,
                       const char *uniformName) {
        *location = (int)glGetUniformLocation(shader->id, uniformName);
        if (*location == -1) {
                fprintf(stderr,
                        "[SHADER:UNIFORM] -> Uniform parameter `%s` not found",
                        uniformName);
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