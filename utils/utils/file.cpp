//
// Created by Michael on 13.02.2021.
//

#include "file.h"

#include "logging.h"
#include "macros.h"
#include <cstdio>

#define OPEN_FILE(name, data) fopen((name).c_str(), data)

std::vector<std::string> File::m_temp_files;

File::FileReadResult File::read_all(const std::string &filename) {
    FILE *file = OPEN_FILE(filename, "r");

    size_t file_length = get_file_size(filename);

    char *buffer = new char[file_length + 1];
    int index = 0;
    int c;
    while ((c = fgetc(file)) != EOF) {

#if defined(PLATFORM_WIN) && defined(FILEFORMAT_CRLF)
        if (c == '\n') { buffer[index++] = '\r'; }
#endif

        buffer[index++] = (char) c;
    }
    buffer[file_length] = '\0';

    fclose(file);
    return {file != nullptr, buffer, file_length, filename};
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

    size_t file_length = get_file_size(filename);
    char *buffer = new char[file_length];
    fread(buffer, file_length, 1, file);
    fclose(file);
    return {file != nullptr, buffer, file_length, filename};
}

void File::write_all_binary(const std::string &filename, const uint8_t *buffer, size_t count) {
    FILE *file = OPEN_FILE(filename, "wb");
    if (buffer != nullptr) fwrite(buffer, sizeof(char), count, file);
    fclose(file);
}

void File::cleanup_temp_files() {
    for (auto &filename : m_temp_files) {
        int result = remove(filename.c_str());
        if (result != 0) { LOGERROR("Could not delete %s", filename.c_str()); }
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
File::FileReadResult::operator bool() const { return success; }

size_t File::get_file_size(const std::string &filename) {
    FILE *file = OPEN_FILE(filename, "rb");

    fseek(file, 0, SEEK_END);
    size_t file_length = ftell(file);

    fclose(file);
    return file_length;
}
