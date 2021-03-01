//
// Created by Michael on 15.02.2021.
//

#include "font.h"

#include <algorithm>

bsw::Font::Font(const std::string &file_path, uint32_t font_size) : m_font_size(font_size) {
    if (FT_Init_FreeType(&m_library)) { ASSERT_NOT_REACHED("Font Library not initialized!"); }

    if (FT_New_Face(m_library, file_path.c_str(), 0, &m_face)) { ASSERT_NOT_REACHED("Font not initialized!"); }

    FT_Set_Pixel_Sizes(m_face, 0, font_size);

    generate_atlas();

    FT_Done_Face(m_face);
    FT_Done_FreeType(m_library);
}

bsw::Font::FontGlyphMetrics &bsw::Font::get_font_data(char character) const { return m_characters[character]; }

const Ref<bsw::Texture2D> &bsw::Font::get_atlas() const { return m_atlas; }

void bsw::Font::generate_atlas() {

    uint32_t atlas_width = 0;
    uint32_t atlas_height = 0;

    for (GLubyte c = 0; c < 128; c++) {
        if (FT_Load_Char(m_face, c, FT_LOAD_RENDER)) {
            std::cerr << "Could not load Glyph '" << c << "'" << std::endl;
            continue;
        }

        FontGlyphMetrics metrics{};
        metrics.size = glm::vec2{m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows};
        metrics.advance = glm::vec2{(m_face->glyph->advance.x), (m_face->glyph->advance.y)};
        metrics.bearing = glm::vec2{m_face->glyph->bitmap_left, m_face->glyph->bitmap_top};
        metrics.ascend = m_face->ascender;
        metrics.descend = m_face->descender;

        metrics.xoffset = atlas_width;
        metrics.yoffset = 0;

        atlas_width += m_face->glyph->bitmap.width + 1;
        atlas_height = std::max(atlas_height, m_face->glyph->bitmap.rows);

        m_characters[c] = metrics;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    m_atlas = create_ref<Texture2D>(atlas_width, atlas_height);
    uint32_t x = 0;
    for (GLubyte c = 0; c < 128; c++) {
        if (FT_Load_Char(m_face, c, FT_LOAD_RENDER)) {
            std::cerr << "Could not load Glyph '" << c << "'" << std::endl;
            continue;
        }

        uint32_t char_width = m_face->glyph->bitmap.width;
        uint32_t char_height = m_face->glyph->bitmap.rows;

        uint32_t bit_depth = 4;
        uint32_t buffer_size = char_width * char_height * bit_depth;
        auto *color_buffer = new uint8_t[buffer_size];

        uint32_t h = 0;
        for (uint32_t j = 0; j < char_height; j++) {
            for (uint32_t i = 0; i < char_width; i++) {
                uint32_t offset = j * char_width + i;

                color_buffer[offset * bit_depth + 0] = 0xff;
                color_buffer[offset * bit_depth + 1] = 0xff;
                color_buffer[offset * bit_depth + 2] = 0xff;
                color_buffer[offset * bit_depth + 3] = m_face->glyph->bitmap.buffer[offset];

                h++;
            }
        }

        m_atlas->set_sub_data(color_buffer, buffer_size, {x, 0}, {char_width, char_height});
        delete[] color_buffer;//Free allocated memory

        x += char_width + 1;
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}
uint32_t bsw::Font::get_font_size() const { return m_font_size; }

uint32_t bsw::Font::get_string_width(const std::string &text) const {
    uint32_t width = 0;
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
        auto metrics = get_font_data(*c);
        width += metrics.advance.x / 64;
    }
    return width;
}

uint32_t bsw::Font::get_string_height(const std::string &text) const {
    uint32_t height = 0;
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
        auto metrics = get_font_data(*c);
        height = std::max(height, (uint32_t) metrics.size.y);
    }
    return height;
}