//
// Created by Michael on 14.02.2021.
//

#pragma once

#include <string>

#include <glad/glad.h>
#include <bsw.h>

namespace bsw {
class Texture2D {
public:
  Texture2D(uint32_t width, uint32_t height, GLint tex_param = GL_REPEAT, uint32_t internalformat = GL_RGBA8, uint32_t dataformat = GL_RGBA);
  explicit Texture2D(const std::string &path);
  virtual ~Texture2D();

  void SetData(void *data, uint32_t size) const;
  void Bind(uint32_t slot) const;
  void Unbind(uint32_t slot) const;

  void SetWidth(uint32_t width) { width_ = width; }
  void SetHeight(uint32_t height) { height_ = height; }
  void SetTextureId(uint32_t texture_id) { texture_id_ = texture_id; }
  bool operator==(const Texture2D &rhs) const {
    return texture_id_ == rhs.texture_id_;
  }

private:
  uint32_t width_{};
  uint32_t height_{};

  uint32_t texture_id_{};

  GLenum internal_format_{};
  GLenum data_format_{};
};
} // namespace bsw