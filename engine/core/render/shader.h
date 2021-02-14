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
  static Shader BasicTexture;

  //  explicit Shader(const std::string &filename);
  Shader(std::string name, const std::string &vertex_src,
         const std::string &fragment_src);
  ~Shader();

  void Bind() const;
  void Unbind() const;

  const std::string &GetName() const { return name_; }

  void SetInt(const std::string &name, int value);
  void SetIntArray(const std::string &name, int* values, uint32_t count);

  void SetFloat(const std::string &name, float value);
  void SetFloat2(const std::string &name, const glm::vec2 &value);
  void SetFloat3(const std::string &name, const glm::vec3 &value);
  void SetFloat4(const std::string &name, const glm::vec4 &value);

  void SetMat3(const std::string &name, const glm::mat3 &matrix);
  void SetMat4(const std::string &name, const glm::mat4 &matrix);

private:
  void Compile(const std::string &vertex_src, const std::string &fragment_src);
  uint32_t CompileShaderSource(const std::string &src, uint32_t type,
                               bool &compile_status) const;

  int GetUniformLocation(const std::string &name);

  std::unordered_map<std::string, uint32_t> uniform_location_cache_;

  uint32_t program_id_;
  std::string name_;
};
} // namespace bsw