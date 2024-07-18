#include "shader.h"

void shaderHandleErrors(struct ShaderProgram *p_shader, int type, unsigned int shader);
void shaderProgramHandleErrors(struct ShaderProgram *p_shader);

int shader_initialize(
    struct ShaderProgram *shader,
    const char *str_vertex_source,
    const char *str_fragment_source,
    const char *str_geometry_source
) {
        shader->str_vertex_source = str_vertex_source;
        shader->str_fragment_source = str_fragment_source;
        shader->str_geometry_source = str_geometry_source;
        shader->id = glCreateProgram();

        return EXIT_SUCCESS;
}

int shader_use(struct ShaderProgram *p_shader) {
        glUseProgram(p_shader->id);

        return EXIT_SUCCESS;
}

int shader_delete_program(struct ShaderProgram *p_shader) {
        glDeleteProgram(p_shader->id);

        return EXIT_SUCCESS;
}

int shader_compile(struct ShaderProgram *p_shader) {
        unsigned int sVertex, sFragment, sGeometry;
        bool hasGeometry = p_shader->str_geometry_source != NULL;


        if (hasGeometry) {
                sGeometry = glCreateShader(GL_GEOMETRY_SHADER);
                glShaderSource(sGeometry, 1, &p_shader->str_geometry_source, NULL);
                glCompileShader(sGeometry);
                shaderHandleErrors(p_shader, 3,sGeometry);

                glAttachShader(p_shader->id, sGeometry);
        }

        sVertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(sVertex, 1, &p_shader->str_vertex_source, NULL);
        glCompileShader(sVertex);
        shaderHandleErrors(p_shader, 1, sVertex);
        glAttachShader(p_shader->id, sVertex);


        sFragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(sFragment, 1, &p_shader->str_fragment_source, NULL);
        glCompileShader(sFragment);
        shaderHandleErrors(p_shader, 2,sFragment);
        glAttachShader(p_shader->id, sFragment);

        glLinkProgram(p_shader->id);

        shaderProgramHandleErrors(p_shader);

        glDeleteShader(sVertex);
        glDeleteShader(sFragment);

        if (hasGeometry) {
                glDeleteShader(sGeometry);
        }

        return EXIT_SUCCESS;
}

void shaderHandleErrors(struct ShaderProgram *p_shaderProgram, int type, unsigned int shader) {
        int success;
        char infoLog[1024];

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);

                const char *source;
                switch (type) {
                        case 1:
                                source = p_shaderProgram->str_vertex_source;
                                break;
                        case 2:
                                source = p_shaderProgram->str_fragment_source;
                                break;
                        case 3:
                                source = p_shaderProgram->str_geometry_source;
                                break;
                        default:
                                break;
                }
                fprintf(stderr, "[SHADER] -> Compile error\nInfo Log:\n%s\nSource:\n%s\n", infoLog, source);
                exit(EXIT_FAILURE);
        }
}
void shaderProgramHandleErrors(struct ShaderProgram *p_shaderProgram) {
        int success;
        char infoLog[1024];

        glGetProgramiv(p_shaderProgram->id, GL_LINK_STATUS, &success);

        if (!success) {
                glGetProgramInfoLog(p_shaderProgram->id, 1024, NULL, infoLog);
                fprintf(stderr, "[SHADER] -> Linking error:\n%s", infoLog);
                exit(EXIT_FAILURE);
        }
}

int uniformGetLocation(
        int *location,
        struct ShaderProgram *p_shader,
        const char *uniformName
) {
        *location = (int)glGetUniformLocation(p_shader->id, uniformName);
        if (*location == -1) {
                fprintf(stderr,
                        "[SHADER:UNIFORM] -> Uniform parameter `%s` not found:\n%s\n%s\n%s\n",
                        uniformName, p_shader->str_vertex_source_path, p_shader->str_fragment_source_path, p_shader->str_geometry_source_path);
                exit(EXIT_FAILURE);
        }

        return EXIT_SUCCESS;
}

int shader_set_mat3(struct ShaderProgram *p_shader, const char *str_uniform_name, mat3 *value) {
        int location;
        uniformGetLocation(&location, p_shader, str_uniform_name);

        glUniformMatrix3fv(location, 1, GL_FALSE, (const GLfloat *)value);

        return EXIT_SUCCESS;
}


int shader_set_mat4(struct ShaderProgram *p_shader, const char *str_uniform_name, mat4 *value) {
        int location;
        uniformGetLocation(&location, p_shader, str_uniform_name);

        glUniformMatrix4fv(location, 1, GL_FALSE, (const GLfloat *)value);

        return EXIT_SUCCESS;
}

int shader_set_vec3f(struct ShaderProgram *p_shader, const char *str_uniform_name, vec3 value) {
        int location;
        uniformGetLocation(&location, p_shader, str_uniform_name);

        glUniform3f(location, value[0], value[1], value[2]);

        return EXIT_SUCCESS;
}

int shaderSetVec4f(struct ShaderProgram *p_shader, const char *str_uniform_name, vec4 value) {
        int location;
        uniformGetLocation(&location, p_shader, str_uniform_name);

        glUniform4f(location, value[0], value[1], value[2], value[3]);

        return EXIT_SUCCESS;
}

int shaderSetVec2f(struct ShaderProgram *p_shader, const char *str_uniform_name, vec2 value) {
        int location;
        uniformGetLocation(&location, p_shader, str_uniform_name);

        glUniform2f(location, value[0], value[1]);

        return EXIT_SUCCESS;
}

int shader_set_float(struct ShaderProgram *p_shader, const char *str_uniform_name, float value) {
        int location;
        uniformGetLocation(&location, p_shader, str_uniform_name);

        glUniform1f(location, value);

        return EXIT_SUCCESS;
}

int shaderSetInt(struct ShaderProgram *p_shader, const char *uniformName, int value) {
        int location;
        uniformGetLocation(&location, p_shader, uniformName);

        glUniform1i(location, value);

        return EXIT_SUCCESS;
}