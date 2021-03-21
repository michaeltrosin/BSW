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
    [[maybe_unused]] static Ref<Texture2D> unknown_texture;

    Texture2D();
    explicit Texture2D(const std::string &path);

    Texture2D(const std::string &path, uint32_t offx, uint32_t offy, uint32_t width, uint32_t height);
    Texture2D(uint32_t width, uint32_t height);

    virtual ~Texture2D();

    /**
     * Sets the data of the texture
     * @param data
     * @param size
     */
    void set_data(void *data, uint32_t size) const;

    /**
     * Sets the data of the texture at a given position and size
     * @param data
     * @param size
     * @param offset
     * @param txsize
     */
    void set_sub_data(void *data, uint32_t size, const glm::vec2 &offset, const glm::vec2 &txsize) const;

    /**
     * Binds the texture
     * @param slot
     */
    virtual void bind(uint32_t slot) const;

    /**
     * Unbinds the texture
     * @param slot
     */
    void unbind(uint32_t slot = 0) const;

    /**
     * Compares this texture id to a other id
     * @param rhs
     * @return
     */
    bool operator==(const Texture2D &rhs) const { return m_texture_id == rhs.m_texture_id; }

    /**
     * Gets the width
     * @return
     */
    uint32_t get_width() const;

    /**
     * Gets the height
     * @return
     */
    uint32_t get_height() const;

private:
    uint32_t m_width{};
    uint32_t m_height{};

    uint32_t m_texture_id{};

    GLenum m_internal_format{};
    GLenum m_data_format{};
};
}// namespace bsw