//
// Created by Michael on 13.02.2021.
//

#pragma once

#include <cstdint>
#include <string>
#include <vector>

class File {
public:
    struct FileReadResult {
        char *data;
        size_t length;
        std::string filename;

        ~FileReadResult() { delete[] data; }

        char &operator[](int) const;
    };

    static FileReadResult read_all(const std::string &filename);
    static void write_all(const std::string &filename, const char *buffer);

    static FileReadResult read_all_binary(const std::string &filename);
    static void write_all_binary(const std::string &filename, const uint8_t *buffer, size_t count);

    static FileReadResult binary_to_string(const uint8_t *buffer, size_t count);
    static std::string create_and_write_temp_file(const uint8_t *buffer, size_t count);
    static std::string create_temp_file();

    static void cleanup_temp_files();

private:
    static std::vector<std::string> m_temp_files;
};