//
// Created by Michael on 24.02.2021.
//

#pragma once

#include <string>
#include <utils/file.h>

using namespace IO;

namespace bsw {
class AssetManager {
public:
    /**
     * Initializes the Assetmanager to the execution path
     * @param execution_path
     */
    static void init(const std::string &execution_path);

    /**
     * Gets the complete asset path from the relative path
     * @param path
     * @return
     */
    static std::string get_asset_path(const std::string &path);

    /**
     * Reads the file complete
     * @param filename
     * @return
     */
    static File::FileReadResult read_all(const std::string &filename);

    /**
     * Writes data to a resource file
     * @param filename
     * @param buffer
     */
    static void write_all(const std::string &filename, const char *buffer);

    /**
     * Reads the file as binary
     * @param filename
     * @return
     */
    static File::FileReadResult read_all_binary(const std::string &filename);

    /**
     * Writes binary data to a resource file
     * @param filename
     * @param buffer
     * @param count
     */
    static void write_all_binary(const std::string &filename, const uint8_t *buffer, size_t count);

private:
    static std::string m_root_path;
    static std::string m_resource_path;
};
}// namespace bsw