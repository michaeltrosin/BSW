//
// Created by Michael on 14.02.2021.
//

#include "texture2d.h"

#include <stb_image/stb_image.h>

bsw::Texture2D::Texture2D(const std::string &path) {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc *data;
    { data = stbi_load(path.c_str(), &width, &height, &channels, 0); }
    m_width = width;
    m_height = height;

    GLenum internal_format = 0, data_format = 0;
    if (channels == 4) {
        internal_format = GL_RGBA8;
        data_format = GL_RGBA;
    } else if (channels == 3) {
        internal_format = GL_RGB8;
        data_format = GL_RGB;
    }

    m_internal_format = internal_format;
    m_data_format = data_format;

    ASSERT(internal_format & data_format, "Format not supported!");

    glCreateTextures(GL_TEXTURE_2D, 1, &m_texture_id);
    glTextureStorage2D(m_texture_id, 1, internal_format, m_width, m_height);

    glTextureParameteri(m_texture_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_texture_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureParameteri(m_texture_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_texture_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureSubImage2D(m_texture_id, 0, 0, 0, m_width, m_height, data_format, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}

bsw::Texture2D::Texture2D(uint32_t width, uint32_t height) : m_width(width), m_height(height) {
    m_internal_format = GL_RGBA8;
    m_data_format = GL_RGBA;

    glCreateTextures(GL_TEXTURE_2D, 1, &m_texture_id);
    glTextureStorage2D(m_texture_id, 1, m_internal_format, m_width, m_height);

    glTextureParameteri(m_texture_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_texture_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureParameteri(m_texture_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_texture_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

bsw::Texture2D::~Texture2D() { glDeleteTextures(1, &m_texture_id); }

void bsw::Texture2D::set_data(void *data, uint32_t size) const {
    uint32_t bpp = m_data_format == GL_RED ? 8 : (m_data_format == GL_RGBA ? 4 : 3);
    ASSERT(size == m_width * m_height * bpp, "Data must be entire texture!");
    glTextureSubImage2D(m_texture_id, 0, 0, 0, m_width, m_height, m_data_format, GL_UNSIGNED_BYTE, data);
}

void bsw::Texture2D::set_sub_data(void *data, uint32_t size, const glm::vec2 &offset, const glm::vec2 &txsize) const {
    uint32_t bpp = m_data_format == GL_RED ? 8 : (m_data_format == GL_RGBA ? 4 : 3);
    ASSERT(size == (uint32_t) txsize.x * (uint32_t) txsize.y * bpp, "Data must be entire texture!");
    glTextureSubImage2D(m_texture_id, 0, (uint32_t) offset.x, (uint32_t) offset.y, (uint32_t) txsize.x, (uint32_t) txsize.y, m_data_format,
                        GL_UNSIGNED_BYTE, data);
}

void bsw::Texture2D::bind(uint32_t slot) const { glBindTextureUnit(slot, m_texture_id); }
void bsw::Texture2D::unbind(uint32_t slot) const { glBindTextureUnit(slot, 0); }
uint32_t bsw::Texture2D::get_width() const { return m_width; }
uint32_t bsw::Texture2D::get_height() const { return m_height; }