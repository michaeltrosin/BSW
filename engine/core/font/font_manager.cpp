//
// Created by Michael on 18.02.2021.
//

#include "font_manager.h"

std::unordered_map<std::string, Single<bsw::Font>> bsw::FontManager::m_font_list;
Single<bsw::Font> bsw::FontManager::default_font;

//FIXME: Make dynamic
void bsw::FontManager::init() { default_font = create_single<Font>(AssetManager::get_asset_path("fonts\\Roboto-Light.ttf"), 24); }

void bsw::FontManager::add_font(const std::string &name, const std::string &font_file, uint32_t font_size) {
    font_size = (uint32_t) mathf::min(font_size, 48);
    m_font_list[name] = create_single<Font>(font_file, font_size);
}

Single<bsw::Font> &bsw::FontManager::get_font(const std::string &name) {
    if (m_font_list.find(name) == m_font_list.end()) return default_font;
    return m_font_list[name];
}
