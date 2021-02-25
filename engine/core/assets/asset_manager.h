//
// Created by Michael on 24.02.2021.
//

#pragma once

#include <string>
#include <utils/file.h>

class AssetManager {
public:
    static void init(const std::string &execution_path);

    static std::string get_asset_path(const std::string& path);

    static File::FileReadResult read_all(const std::string &filename);
    static void write_all(const std::string &filename, const char *buffer);

    static File::FileReadResult read_all_binary(const std::string &filename);
    static void write_all_binary(const std::string &filename, const uint8_t *buffer, size_t count);

    static File::FileReadResult binary_to_string(const uint8_t *buffer, size_t count);
private:
    static std::string m_root_path;
    static std::string m_resource_path;
};
