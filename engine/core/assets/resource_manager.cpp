//
// Created by Michael on 20.03.2021.
//

#include "resource_manager.h"

#include <core/font/font.h>
#include <core/render/shading/shader.h>

bsw::Resource<bsw::Shader> bsw::ResourceManager::load_shader(const std::string &path) {
    std::string asset_path = AssetManager::get_asset_path(path);
    Resource<Shader> shader = create_ref<Shader>(asset_path);
    return shader;
}

bsw::Resource<bsw::Texture2D> bsw::ResourceManager::load_texture(const std::string &path) {
    std::string asset_path = AssetManager::get_asset_path(path);
    Resource<Texture2D> texture = create_ref<Texture2D>(asset_path);
    return texture;
}

bsw::Resource<bsw::Texture2D> bsw::ResourceManager::load_texture(const std::string &path, uint32_t offx, uint32_t offy, uint32_t width,
                                                                 uint32_t height) {
    std::string asset_path = AssetManager::get_asset_path(path);
    Resource<Texture2D> texture = create_ref<Texture2D>(asset_path, offx, offy, width, height);
    return texture;
}

bsw::Resource<bsw::Font> bsw::ResourceManager::load_font(const std::string &path, uint32_t font_size) {
    std::string asset_path = AssetManager::get_asset_path(path);
    Resource<Font> font = create_ref<Font>(path, font_size);
    return font;
}
