//
// Created by Michael on 18.02.2021.
//

#include "font_manager.h"

std::unordered_map<std::string, Ref<bsw::Font>> bsw::FontManager::m_font_list;

Ref<bsw::Font> bsw::FontManager::get_font(const std::string &name) {
    if (m_font_list.find(name) == m_font_list.end()) { ASSERT_NOT_REACHED("Font not found!"); }
    return m_font_list[name];
}

void bsw::FontManager::add_font(const std::string &name, const Ref<bsw::Font> &font) { m_font_list[name] = font; }
