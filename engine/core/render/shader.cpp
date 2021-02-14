//
// Created by Michael on 13.02.2021.
//

#include "shader.h"

#include <bsw.h>
#include <utility>
#include <vector>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace bsw {
// Shader::Shader(const std::string &filename) {}
Shader::Shader(std::string name, const std::string &vertex_src,
               const std::string &fragment_src)
    : name_(std::move(name)), program_id_{0} {
  ASSERT_TYPE(uint32_t, GLuint);

  Compile(vertex_src, fragment_src);
}

Shader::~Shader() { glDeleteProgram(program_id_); }

void Shader::Bind() const { glUseProgram(program_id_); }
void Shader::Unbind() const { glUseProgram(0); }
void Shader::Compile(const std::string &vertex_src,
                     const std::string &fragment_src) {

  // TODO: Optimize shader linking

  GLuint program = glCreateProgram();

  bool status_vert;
  bool status_frag;
  GLuint vertex =
      CompileShaderSource(vertex_src, GL_VERTEX_SHADER, status_vert);

  if (status_vert)
    glAttachShader(program, vertex);

  GLuint fragment =
      CompileShaderSource(fragment_src, GL_FRAGMENT_SHADER, status_frag);
  if (status_frag)
    glAttachShader(program, fragment);

  glLinkProgram(program);

  GLint is_linked = 0;
  glGetProgramiv(program, GL_LINK_STATUS, &is_linked);
  if (is_linked == GL_FALSE) {
    GLint max_length = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_length);

    std::vector<GLchar> info_log(max_length);
    glGetProgramInfoLog(program, max_length, &max_length, &info_log[0]);

    glDeleteProgram(program);

    if (status_vert)
      glDeleteShader(vertex);
    if (status_frag)
      glDeleteShader(fragment);

    std::cerr << info_log.data() << std::endl;
    ASSERT(false, "Shader compilation failure!");
    return;
  }

  program_id_ = program;

  if (status_vert) {
    glDetachShader(program, vertex);
    glDeleteShader(vertex);
  }
  if (status_frag) {
    glDetachShader(program, fragment);
    glDeleteShader(fragment);
  }
}

GLuint Shader::CompileShaderSource(const std::string &src, GLenum type,
                                   bool &compile_status) const {
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

int Shader::GetUniformLocation(const std::string &name) {
  if (uniform_location_cache_.find(name) != uniform_location_cache_.end()) {
    return uniform_location_cache_[name];
  }
  int location = glGetUniformLocation(program_id_, name.c_str());
  if (location == -1) {
    std::cerr << "Uniform: " << name << " not found!" << std::endl;
  }
  uniform_location_cache_[name] = location;
  return location;
}

void Shader::SetInt(const std::string &name, int value) {
  int location = GetUniformLocation(name);
  if (location != -1)
    glUniform1i(location, value);
}

void Shader::SetIntArray(const std::string &name, int *values, uint32_t count) {
  int location = GetUniformLocation(name);
  if (location != -1)
    glUniform1iv(location, count, values);
}

void Shader::SetFloat(const std::string &name, float value) {
  int location = GetUniformLocation(name);
  if (location != -1)
    glUniform1f(location, value);
}

void Shader::SetFloat2(const std::string &name, const glm::vec2 &value) {
  int location = GetUniformLocation(name);
  if (location != -1)
    glUniform2f(location, value.x, value.y);
}

void Shader::SetFloat3(const std::string &name, const glm::vec3 &value) {
  int location = GetUniformLocation(name);
  if (location != -1)
    glUniform3f(location, value.x, value.y, value.z);
}

void Shader::SetFloat4(const std::string &name, const glm::vec4 &value) {
  int location = GetUniformLocation(name);
  if (location != -1)
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::SetMat3(const std::string &name, const glm::mat3 &matrix) {
  int location = GetUniformLocation(name);
  if (location != -1)
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &matrix) {
  int location = GetUniformLocation(name);
  if (location != -1)
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

} // namespace bsw