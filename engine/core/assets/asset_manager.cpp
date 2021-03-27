//
// Created by Michael on 24.02.2021.
//

#include "asset_manager.h"

#include <core/font/font.h>
#include <core/render/shading/shader.h>
#include <iostream>

std::string bsw::AssetManager::m_root_path;
std::string bsw::AssetManager::m_resource_path;

std::string bsw::AssetManager::get_asset_path(const std::string &path) { return std::string(m_resource_path).append(path); }

void bsw::AssetManager::init(const std::string &execution_path) {
    m_root_path = execution_path.substr(0, execution_path.find_last_of('\\'));

    m_resource_path = std::string(m_root_path).append("\\resources\\");

    std::cout << m_resource_path << std::endl;
}

File::FileReadResult bsw::AssetManager::read_all(const std::string &filename) { return File::read_all(get_asset_path(filename)); }

void bsw::AssetManager::write_all(const std::string &filename, const char *buffer) { File::write_all(get_asset_path(filename), buffer); }

File::FileReadResult bsw::AssetManager::read_all_binary(const std::string &filename) { return File::read_all_binary(get_asset_path(filename)); }

void bsw::AssetManager::write_all_binary(const std::string &filename, const uint8_t *buffer, size_t count) {
    File::write_all_binary(get_asset_path(filename), buffer, count);
}

std::shared_ptr<bsw::Shader> bsw::AssetManager::load_shader(const std::string &path) {
    std::string asset_path = AssetManager::get_asset_path(path);
    std::shared_ptr<Shader> shader = std::make_shared<Shader>(asset_path);
    return shader;
}

std::shared_ptr<bsw::Texture2D> bsw::AssetManager::load_texture(const std::string &path) {
    std::string asset_path = AssetManager::get_asset_path(path);
    std::shared_ptr<Texture2D> texture = std::make_shared<Texture2D>(asset_path);
    return texture;
}

std::shared_ptr<bsw::Texture2D> bsw::AssetManager::load_texture(const std::string &path, uint32_t offx, uint32_t offy, uint32_t width,
                                                                uint32_t height) {
    std::string asset_path = AssetManager::get_asset_path(path);
    std::shared_ptr<Texture2D> texture = std::make_shared<Texture2D>(asset_path, offx, offy, width, height);
    return texture;
}

std::shared_ptr<bsw::Font> bsw::AssetManager::load_font(const std::string &path, uint32_t font_size) {
    std::string asset_path = AssetManager::get_asset_path(path);
    std::shared_ptr<Font> font = std::make_shared<Font>(asset_path, font_size);
    return font;
}