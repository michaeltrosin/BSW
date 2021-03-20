//
// Created by Michael on 18.02.2021.
//

#pragma once

#include <bsw.h>
#include <core/font/font.h>

#include <vector>

//TODO: Add direct font loading from name

namespace bsw {
class FontManager {
public:
    static void shutdown() {}
    //R"(F:\BSW\resources\fonts\Roboto-Light.ttf)"

    /**
     * Adds a font with the name 'name' based on a font file and a font size
     * @param name
     * @param font_file
     * @param font_size
     */
    static void add_font(const std::string &name, const Ref<Font> &font);

    /**
     * Gets the font from a given name
     * @param name
     * @return
     */
    static Ref<Font> get_font(const std::string &name);

private:
    static std::unordered_map<std::string, Ref<Font>> m_font_list;
};
}// namespace bsw