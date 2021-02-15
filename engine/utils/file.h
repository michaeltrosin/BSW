//
// Created by Michael on 13.02.2021.
//

#pragma once

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

  static FileReadResult ReadAll(const std::string &filename);
  static void WriteAll(const std::string &filename, const char *buffer);

  static FileReadResult ReadAllBinary(const std::string &filename);
  static void WriteAllBinary(const std::string &filename,
                             const unsigned char *buffer, size_t count);

  static FileReadResult BinaryToString(const unsigned char* buffer, size_t count);
  static std::string ToTempFile(const unsigned char* buffer, size_t count);

  static void CleanupTempFiles();

private:
  static std::vector<std::string> temp_files_;
};