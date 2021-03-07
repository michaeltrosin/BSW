//
// Created by Michael on 13.02.2021.
//

#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

#define STYPE_BOOL  0
#define STYPE_INT   1
#define STYPE_FLOAT 2
#define STYPE_VEC_2 3
#define STYPE_VEC_3 4
#define STYPE_VEC_4 5
#define STYPE_MAT_3 6
#define STYPE_MAT_4 7

namespace bsw {
class Shader;

class ShaderStruct {
public:
    union Value {
        bool bval;
        int ival;
        float fval;
        glm::vec2 vec_2_val;
        glm::vec3 vec_3_val;
        glm::vec4 vec_4_val;

        glm::mat3 mat_3_val;
        glm::mat4 mat_4_val;
    };

    friend Shader;

    static ShaderStruct construct(const std::unordered_map<std::string, uint32_t> &template_data);

    bool exists(const std::string &name);

    void set(const std::string &name, int value);
    //    void set(const std::string &name, int *values, uint32_t count);

    void set(const std::string &name, bool value);

    void set(const std::string &name, float value);
    void set(const std::string &name, const glm::vec2 &value);
    void set(const std::string &name, const glm::vec3 &value);
    void set(const std::string &name, const glm::vec4 &value);

    void set(const std::string &name, const glm::mat3 &matrix);
    void set(const std::string &name, const glm::mat4 &matrix);

private:
    std::unordered_map<std::string, std::tuple<uint32_t, Value>> m_struct_content;// name, value
    std::unordered_map<std::string, uint32_t> m_template;
};

class Shader {
public:
    explicit Shader(std::string filename);
    //    Shader(std::string name, const std::string &vertex_file, const std::string &fragment_file);
    ~Shader();

    void bind() const;
    void unbind() const;

    const std::string &get_name() const { return m_name; }

    void set_struct(const std::string &name, const ShaderStruct &shader_struct);

    void set_int(const std::string &name, int value);
    void set_int_array(const std::string &name, int *values, uint32_t count);

    void set_bool(const std::string &name, bool value);

    void set_float(const std::string &name, float value);
    void set_float_2(const std::string &name, const glm::vec2 &value);
    void set_float_3(const std::string &name, const glm::vec3 &value);
    void set_float_4(const std::string &name, const glm::vec4 &value);

    void set_mat_3(const std::string &name, const glm::mat3 &matrix);
    void set_mat_4(const std::string &name, const glm::mat4 &matrix);

private:
    void compile(const std::string &vertex_src, const std::string &fragment_src);
    uint32_t compile_shader_source(const std::string &src, uint32_t type, bool &compile_status) const;

    int get_uniform_location(const std::string &name);

    std::unordered_map<std::string, uint32_t> m_uniform_location_cache;

    uint32_t m_program_id;
    std::string m_name;
};
}// namespace bsw