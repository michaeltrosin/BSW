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
        bool success{false};

        char *data;
        size_t length;
        std::string filename;

        ~FileReadResult() { delete[] data; }

        explicit operator bool() const;
        char &operator[](int) const;
    };

    /**
     * Reads a file completely
     * @param filename
     * @return
     */
    static FileReadResult read_all(const std::string &filename);

    /**
     * Writes data to a file
     * @param filename
     * @param buffer
     */
    static void write_all(const std::string &filename, const char *buffer);

    /**
     * Reads a binary file completely
     * @param filename
     * @return
     */
    static FileReadResult read_all_binary(const std::string &filename);

    /**
     * Writes binary data to a file
     * @param filename
     * @param buffer
     * @param count
     */
    static void write_all_binary(const std::string &filename, const uint8_t *buffer, size_t count);

    /**
     * Converts binary data to a string
     *
     * Will write to a temp file
     * @param buffer
     * @param count
     * @return
     */
    static FileReadResult binary_to_string(const uint8_t *buffer, size_t count);

    /**
     * Creates and writes a temp file and returns the path
     * @param buffer
     * @param count
     * @return
     */
    static std::string create_and_write_temp_file(const uint8_t *buffer, size_t count);

    /**
     * Creates a temp file and returns the path
     * @return
     */
    static std::string create_temp_file();

    /**
     * Deletes all temp files
     */
    static void cleanup_temp_files();

    /**
     * Gets the size of a given file
     * @param filename
     * @return
     */
    static size_t get_file_size(const std::string &filename);

private:
    static std::vector<std::string> m_temp_files;
};