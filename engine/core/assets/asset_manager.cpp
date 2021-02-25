//
// Created by Michael on 24.02.2021.
//

#include "asset_manager.h"

#include <iostream>

std::string AssetManager::m_root_path;
std::string AssetManager::m_resource_path;

std::string AssetManager::get_asset_path(const std::string &path) { return std::string(m_resource_path).append(path); }

void AssetManager::init(const std::string &execution_path) {
    m_root_path = execution_path.substr(0, execution_path.find_last_of('\\'));

    m_resource_path = std::string(m_root_path).append("\\resources\\");

    std::cout << m_resource_path << std::endl;
}

File::FileReadResult AssetManager::read_all(const std::string &filename) { return File::read_all(get_asset_path(filename)); }
void AssetManager::write_all(const std::string &filename, const char *buffer) { File::write_all(get_asset_path(filename), buffer); }
File::FileReadResult AssetManager::read_all_binary(const std::string &filename) { return File::read_all_binary(get_asset_path(filename)); }
void AssetManager::write_all_binary(const std::string &filename, const uint8_t *buffer, size_t count) {File::write_all_binary(get_asset_path(filename), buffer, count);}
