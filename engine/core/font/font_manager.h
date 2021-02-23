//
// Created by Michael on 18.02.2021.
//

#pragma once

#include <bsw.h>
#include <core/font/font.h>

#include <vector>

namespace bsw {
class FontManager {
public:
    static Single<Font> default_font;

    static void init();
    static void shutdown() {}
    //R"(F:\BSW\resources\fonts\Roboto-Light.ttf)"
    static void add_font(const std::string &name, const std::string &font_file, uint32_t font_size);
    static Single<Font> &get_font(const std::string &name);

private:
    static std::unordered_map<std::string, Single<Font>> m_font_list;
};
}// namespace bsw