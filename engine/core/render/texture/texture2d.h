//
// Created by Michael on 14.02.2021.
//

#pragma once

// clang-format off
#include <glad/glad.h>
#include <bsw.h>
// clang-format on

#include <glm/glm.hpp>
#include <string>

namespace bsw {
class Texture2D {
public:
    Texture2D();
    explicit Texture2D(const std::string &path);
    Texture2D(uint32_t width, uint32_t height);
    virtual ~Texture2D();

    void set_data(void *data, uint32_t size) const;
    void set_sub_data(void *data, uint32_t size, const glm::vec2 &offset, const glm::vec2 &txsize) const;

    virtual void bind(uint32_t slot) const;
    void unbind(uint32_t slot = 0) const;

    void set_width(uint32_t width) { m_width = width; }
    void set_height(uint32_t height) { m_height = height; }

    bool operator==(const Texture2D &rhs) const { return m_texture_id == rhs.m_texture_id; }

    uint32_t get_width() const;
    uint32_t get_height() const;

private:
    uint32_t m_width{};
    uint32_t m_height{};

    uint32_t m_texture_id{};

    GLenum m_internal_format{};
    GLenum m_data_format{};
};
}// namespace bsw