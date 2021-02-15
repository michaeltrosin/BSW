//
// Created by Michael on 14.02.2021.
//

#include "texture2d.h"

#include <stb_image/stb_image.h>

namespace bsw {

Texture2D::Texture2D(const std::string &path) {
  int width, height, channels;
  stbi_set_flip_vertically_on_load(1);
  stbi_uc *data;
  { data = stbi_load(path.c_str(), &width, &height, &channels, 0); }
  width_ = width;
  height_ = height;

  GLenum internal_format = 0, data_format = 0;
  if (channels == 4) {
    internal_format = GL_RGBA8;
    data_format = GL_RGBA;
  } else if (channels == 3) {
    internal_format = GL_RGB8;
    data_format = GL_RGB;
  }

  internal_format_ = internal_format;
  data_format_ = data_format;

  ASSERT(internal_format & data_format, "Format not supported!");

  glCreateTextures(GL_TEXTURE_2D, 1, &texture_id_);
  glTextureStorage2D(texture_id_, 1, internal_format, width_, height_);

  glTextureParameteri(texture_id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(texture_id_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTextureParameteri(texture_id_, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTextureParameteri(texture_id_, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTextureSubImage2D(texture_id_, 0, 0, 0, width_, height_, data_format,
                      GL_UNSIGNED_BYTE, data);

  stbi_image_free(data);
}

Texture2D::Texture2D(uint32_t width, uint32_t height, GLint tex_param,
                     uint32_t internalformat, uint32_t dataformat)
    : width_(width), height_(height) {
  internal_format_ = internalformat;
  data_format_ = dataformat;

  glCreateTextures(GL_TEXTURE_2D, 1, &texture_id_);
  glTextureStorage2D(texture_id_, 1, internal_format_, width_, height_);

  glTextureParameteri(texture_id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(texture_id_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTextureParameteri(texture_id_, GL_TEXTURE_WRAP_S, tex_param);
  glTextureParameteri(texture_id_, GL_TEXTURE_WRAP_T, tex_param);
}

Texture2D::~Texture2D() { glDeleteTextures(1, &texture_id_); }

void Texture2D::SetData(void *data, uint32_t size) const {
  uint32_t bpp = data_format_ == GL_RED ? 8 : (data_format_ == GL_RGBA ? 4 : 3);
  ASSERT(size == width_ * height_ * bpp, "Data must be entire texture!");
  glTextureSubImage2D(texture_id_, 0, 0, 0, width_, height_, data_format_,
                      GL_UNSIGNED_BYTE, data);
}
void Texture2D::Bind(uint32_t slot = 0) const {
  glBindTextureUnit(slot, texture_id_);
}
void Texture2D::Unbind(uint32_t slot = 0) const { glBindTextureUnit(slot, 0); }
} // namespace bsw