//
// Created by Michael on 13.02.2021.
//

#include "file.h"

#include <cstdio>

#include <iostream>

#define OPEN_FILE(name, data) fopen((name).c_str(), data)
#define OPEN_FILE_C(name, data) fopen(name, data)

std::vector<std::string> File::m_temp_files;

File::FileReadResult File::read_all(const std::string &filename) {
    FILE *file = OPEN_FILE(filename, "r");
    std::cout << filename << std::endl;

    fseek(file, 0, SEEK_END);
    size_t file_length = ftell(file);
    rewind(file);

    char *buffer = new char[file_length + 1];
    int index = 0;
    int c;
    while ((c = fgetc(file)) != EOF) {
        buffer[index] = (char) c;
        index++;
    }
    buffer[file_length] = '\0';

    fclose(file);
    return {buffer, file_length, filename};
}

void File::write_all(const std::string &filename, const char *buffer) {
    FILE *file = OPEN_FILE(filename, "w");

    int index = 0;
    int c;
    if (buffer != nullptr)
        while ((c = (int) ((uint8_t) buffer[index])) != '\0') {
            fputc(c, file);
            index++;
        }

    fclose(file);
}

File::FileReadResult File::read_all_binary(const std::string &filename) {
    FILE *file = OPEN_FILE(filename, "rb");

    fseek(file, 0, SEEK_END);
    size_t file_length = ftell(file);
    rewind(file);

    char *buffer = new char[file_length];
    fread(buffer, file_length, 1, file);
    fclose(file);
    return {buffer, file_length, filename};
}

void File::write_all_binary(const std::string &filename, const uint8_t *buffer, size_t count) {
    FILE *file = OPEN_FILE(filename, "wb");
    if (buffer != nullptr) fwrite(buffer, sizeof(char), count, file);
    fclose(file);
}

void File::cleanup_temp_files() {
    for (auto &filename : m_temp_files) {
        int result = remove(filename.c_str());
        if (result != 0) { printf("Could not delete %s\n", filename.c_str()); }
    }
}

File::FileReadResult File::binary_to_string(const uint8_t *buffer, size_t count) {
    std::string filename(std::tmpnam(nullptr));
    filename.insert(0, getenv("TEMP"));

    write_all_binary(filename, buffer, count);
    FileReadResult r = read_all(filename);

    m_temp_files.push_back(filename);
    return r;
}

std::string File::create_and_write_temp_file(const uint8_t *buffer, size_t count) {
    std::string filename(std::tmpnam(nullptr));
    filename.insert(0, getenv("TEMP"));

    write_all_binary(filename, buffer, count);

    m_temp_files.push_back(filename);
    return filename;
}

std::string File::create_temp_file() {
    std::string filename(std::tmpnam(nullptr));
    filename.insert(0, getenv("TEMP"));

    write_all_binary(filename, nullptr, 0);

    m_temp_files.push_back(filename);
    return filename;
}

char &File::FileReadResult::operator[](int index) const { return data[index]; }