//
// Created by Michael on 13.02.2021.
//

#include "shader.h"

#include <bsw.h>
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>
#include <vector>

bsw::Shader::Shader(std::string filename) : m_name(std::move(filename)), m_program_id{0} {
    ASSERT_TYPE(uint32_t, GLuint);

    std::string vert_path = std::string(m_name).append(".vert");
    std::string frag_path = std::string(m_name).append(".frag");

    auto read_vert = AssetManager::read_all(vert_path);
    auto read_frag = AssetManager::read_all(frag_path);

    const char *vert_data = read_vert.data;
    const char *frag_data = read_frag.data;

    compile(vert_data, frag_data);
}

bsw::Shader::~Shader() { glDeleteProgram(m_program_id); }

void bsw::Shader::bind() const { glUseProgram(m_program_id); }

void bsw::Shader::unbind() const { glUseProgram(0); }

void bsw::Shader::compile(const char *vertex_src, const char *fragment_src) {
    // TODO: Optimize shader linking
    GLuint program = glCreateProgram();

    std::printf("%s\n", fragment_src);

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

GLuint bsw::Shader::compile_shader_source(const char *src, GLenum type, bool &compile_status) const {
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &src, nullptr);
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

void bsw::Shader::set_struct(const std::string &name, const ShaderStruct &shader_struct) {
    for (const auto &values : shader_struct.m_struct_content) {
        std::string value_name = name;
        auto [type, value] = values.second;
        value_name = value_name.append(".");
        value_name = value_name.append(values.first);

        switch (type) {
            case STYPE_BOOL: set_bool(value_name, value.bval); break;
            case STYPE_INT: set_int(value_name, value.ival); break;
            case STYPE_FLOAT: set_float(value_name, value.fval); break;

            case STYPE_VEC_2: set_float_2(value_name, value.vec_2_val); break;
            case STYPE_VEC_3: set_float_3(value_name, value.vec_3_val); break;
            case STYPE_VEC_4: set_float_4(value_name, value.vec_4_val); break;

            case STYPE_MAT_3: set_mat_3(value_name, value.mat_3_val); break;
            case STYPE_MAT_4: set_mat_4(value_name, value.mat_4_val); break;
            default: break;
        }
    }
}

void bsw::ShaderStruct::set(const std::string &name, int value) {
    if (!exists(name)) return;
    Value val{};
    val.ival = value;
    m_struct_content[name] = std::make_pair(STYPE_INT, val);
}

//void bsw::ShaderStruct::set(const std::string &name, int *values, uint32_t count) {}

void bsw::ShaderStruct::set(const std::string &name, bool value) {
    if (!exists(name)) return;
    Value val{};
    val.bval = value;
    m_struct_content[name] = std::make_pair(STYPE_BOOL, val);
}
void bsw::ShaderStruct::set(const std::string &name, float value) {
    if (!exists(name)) return;
    Value val{};
    val.fval = value;
    m_struct_content[name] = std::make_pair(STYPE_FLOAT, val);
}
void bsw::ShaderStruct::set(const std::string &name, const glm::vec2 &value) {
    if (!exists(name)) return;
    Value val{};
    val.vec_2_val = value;
    m_struct_content[name] = std::make_pair(STYPE_VEC_2, val);
}
void bsw::ShaderStruct::set(const std::string &name, const glm::vec3 &value) {
    if (!exists(name)) return;
    Value val{};
    val.vec_3_val = value;
    m_struct_content[name] = std::make_pair(STYPE_VEC_3, val);
}
void bsw::ShaderStruct::set(const std::string &name, const glm::vec4 &value) {
    if (!exists(name)) return;
    Value val{};
    val.vec_4_val = value;
    m_struct_content[name] = std::make_pair(STYPE_VEC_4, val);
}
void bsw::ShaderStruct::set(const std::string &name, const glm::mat3 &matrix) {
    if (!exists(name)) return;
    Value val{};
    val.mat_3_val = matrix;
    m_struct_content[name] = std::make_pair(STYPE_MAT_3, val);
}
void bsw::ShaderStruct::set(const std::string &name, const glm::mat4 &matrix) {
    if (!exists(name)) return;
    Value val{};
    val.mat_4_val = matrix;
    m_struct_content[name] = std::make_pair(STYPE_MAT_4, val);
}
bsw::ShaderStruct bsw::ShaderStruct::construct(const std::unordered_map<std::string, uint32_t> &template_data) {
    ShaderStruct result;
    result.m_template = template_data;
    return result;
}
bool bsw::ShaderStruct::exists(const std::string &name) { return m_template.find(name) != m_template.end(); }
