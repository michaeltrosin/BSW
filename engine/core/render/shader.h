//
// Created by Michael on 13.02.2021.
//

#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

namespace bsw {
class Shader {
public:
    static Shader basic_texture;

    //  explicit Shader(const std::string &filename);
    Shader(std::string name, const std::string &vertex_src, const std::string &fragment_src);
    ~Shader();

    void bind() const;
    void unbind() const;

    const std::string &get_name() const { return m_name; }

    void set_int(const std::string &name, int value);
    void set_int_array(const std::string &name, int *values, uint32_t count);

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