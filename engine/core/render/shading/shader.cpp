//
// Created by Michael on 13.02.2021.
//

#include "shader.h"

#include <bsw.h>
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>
#include <utility>
#include <vector>

// Shader::Shader(const std::string &filename) {}
bsw::Shader::Shader(std::string name, const std::string &vertex_src, const std::string &fragment_src) : m_name(std::move(name)), m_program_id{0} {
    ASSERT_TYPE(uint32_t, GLuint);

    compile(vertex_src, fragment_src);
}

bsw::Shader::~Shader() { glDeleteProgram(m_program_id); }

void bsw::Shader::bind() const { glUseProgram(m_program_id); }
void bsw::Shader::unbind() const { glUseProgram(0); }
void bsw::Shader::compile(const std::string &vertex_src, const std::string &fragment_src) {

    // TODO: Optimize shader linking

    GLuint program = glCreateProgram();

    bool status_vert;
    bool status_frag;
    GLuint vertex = compile_shader_source(vertex_src, GL_VERTEX_SHADER, status_vert);

    if (status_vert) glAttachShader(program, vertex);

    GLuint fragment = compile_shader_source(fragment_src, GL_FRAGMENT_SHADER, status_frag);
    if (status_frag) glAttachShader(program, fragment);

    glLinkProgram(program);

    GLint is_linked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &is_linked);
    if (is_linked == GL_FALSE) {
        GLint max_length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_length);

        std::vector<GLchar> info_log(max_length);
        glGetProgramInfoLog(program, max_length, &max_length, &info_log[0]);

        glDeleteProgram(program);

        if (status_vert) glDeleteShader(vertex);
        if (status_frag) glDeleteShader(fragment);

        std::cerr << info_log.data() << std::endl;
        ASSERT(false, "Shader compilation failure!");
        return;
    }

    m_program_id = program;

    if (status_vert) {
        glDetachShader(program, vertex);
        glDeleteShader(vertex);
    }
    if (status_frag) {
        glDetachShader(program, fragment);
        glDeleteShader(fragment);
    }
}

GLuint bsw::Shader::compile_shader_source(const std::string &src, GLenum type, bool &compile_status) const {
    GLuint shader = glCreateShader(type);
    const GLchar *src_cstr = src.c_str();

    glShaderSource(shader, 1, &src_cstr, nullptr);
    glCompileShader(shader);

    GLint is_compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);

    if (is_compiled == GL_FALSE) {
        GLint max_length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

        std::vector<GLchar> info_log(max_length);
        glGetShaderInfoLog(shader, max_length, &max_length, &info_log[0]);

        glDeleteShader(shader);

        std::cerr << info_log.data() << std::endl;
        ASSERT_NOT_REACHED("Shader compilation failure!");

        compile_status = false;
        return 0;
    }

    compile_status = true;
    return shader;
}

int bsw::Shader::get_uniform_location(const std::string &name) {
    if (m_uniform_location_cache.find(name) != m_uniform_location_cache.end()) { return m_uniform_location_cache[name]; }
    int location = glGetUniformLocation(m_program_id, name.c_str());
    if (location == -1) { std::cerr << "Uniform: " << name << " not found!" << std::endl; }
    m_uniform_location_cache[name] = location;
    return location;
}

void bsw::Shader::set_int(const std::string &name, int value) {
    int location = get_uniform_location(name);
    if (location != -1) glUniform1i(location, value);
}

void bsw::Shader::set_int_array(const std::string &name, int *values, uint32_t count) {
    int location = get_uniform_location(name);
    if (location != -1) glUniform1iv(location, count, values);
}

void bsw::Shader::set_float(const std::string &name, float value) {
    int location = get_uniform_location(name);
    if (location != -1) glUniform1f(location, value);
}

void bsw::Shader::set_float_2(const std::string &name, const glm::vec2 &value) {
    int location = get_uniform_location(name);
    if (location != -1) glUniform2f(location, value.x, value.y);
}

void bsw::Shader::set_float_3(const std::string &name, const glm::vec3 &value) {
    int location = get_uniform_location(name);
    if (location != -1) glUniform3f(location, value.x, value.y, value.z);
}

void bsw::Shader::set_float_4(const std::string &name, const glm::vec4 &value) {
    int location = get_uniform_location(name);
    if (location != -1) glUniform4f(location, value.x, value.y, value.z, value.w);
}

void bsw::Shader::set_mat_3(const std::string &name, const glm::mat3 &matrix) {
    int location = get_uniform_location(name);
    if (location != -1) glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void bsw::Shader::set_mat_4(const std::string &name, const glm::mat4 &matrix) {
    int location = get_uniform_location(name);
    if (location != -1) glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
void bsw::Shader::set_bool(const std::string &name, bool value) { set_int(name, (int) value); }
