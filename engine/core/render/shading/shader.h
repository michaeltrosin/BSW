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
    friend Shader;

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

    /**
     * Constructs a new ShaderStruct of template Data
     * @param template_data
     * @return
     */
    static ShaderStruct construct(const std::unordered_map<std::string, uint32_t> &template_data);

    /**
     * Returns true if a element with a name exists
     * @param name
     * @return
     */
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

    /**
     * Binds the Shader
     */
    void bind() const;

    /**
     * Unbinds the Shader
     */
    void unbind() const;

    /**
     * Returns the shader name
     * @return
     */
    const std::string &get_name() const { return m_name; }

    /**
     * Sets a Shader Struct
     * @param name
     * @param shader_struct
     */
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
    /**
     * Compiles the shader from vertex and fragment sources
     * @param vertex_src
     * @param fragment_src
     */
    void compile(const char *vertex_src, const char *fragment_src);

    /**
     * Compiles a single shader source with a given type
     *
     * @param src
     * @param type
     * @param compile_status will return true if compiled successfully
     * @return
     */
    uint32_t compile_shader_source(const char *src, uint32_t type, bool &compile_status) const;

    /**
     * Gets a uniform location from a given name
     * @param name
     * @return
     */
    int get_uniform_location(const std::string &name);

    std::unordered_map<std::string, uint32_t> m_uniform_location_cache;

    uint32_t m_program_id;
    std::string m_name;
};
}// namespace bsw