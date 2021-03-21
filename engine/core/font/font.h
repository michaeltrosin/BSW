//
// Created by Michael on 15.02.2021.
//

#pragma once

#include <bsw.h>
#include <ft2build.h>

#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

#include <freetype/freetype.h>
#include FT_FREETYPE_H

#include <core/texture/texture2d.h>

//TODO: Add font handler (caching font sizes with names)
namespace bsw {
class Font {
public:
    struct FontGlyphMetrics {
        glm::vec2 size;
        glm::vec2 advance;
        glm::vec2 bearing;

        int32_t ascend;
        int32_t descend;

        int32_t xoffset;
        int32_t yoffset;
    };

    Font(const std::string &file_path, uint32_t font_size = 24);

    /**
     * Gets the font metrics from a character
     * @param character
     * @return
     */
    FontGlyphMetrics &get_font_data(char character) const;

    /**
     * Gets the atlas texture
     * @return
     */
    const Ref<Texture2D> &get_atlas() const;

    /**
     * Gets the font size
     * @return
     */
    uint32_t get_font_size() const;

    /**
     * Gets the width of a given string
     * @param text
     * @return
     */
    uint32_t get_string_width(const std::string &text) const;

    /**
     * Gets the height of a given string
     * @param text
     * @return
     */
    uint32_t get_string_height(const std::string &text) const;

private:
    void generate_atlas();

    mutable std::unordered_map<char, FontGlyphMetrics> m_characters;

    Ref<Texture2D> m_atlas;
    uint32_t m_font_size;

    FT_Library m_library{};
    FT_Face m_face{};
};
}// namespace bsw
