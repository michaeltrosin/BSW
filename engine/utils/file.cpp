//
// Created by Michael on 13.02.2021.
//

#include "file.h"

#include <cstdio>

#define OPEN_FILE(name, data) fopen((name).c_str(), data)
#define OPEN_FILE_C(name, data) fopen(name, data)

std::vector<std::string> File::temp_files_;

File::FileReadResult File::ReadAll(const std::string &filename) {
  FILE *file = OPEN_FILE(filename, "r");

  fseek(file, 0, SEEK_END);
  size_t file_length = ftell(file);
  rewind(file);

  char *buffer = new char[file_length + 1];
  int index = 0;
  int c;
  while ((c = fgetc(file)) != EOF) {
    buffer[index] = (char)c;
    index++;
  }
  buffer[file_length] = '\0';

  fclose(file);
  return {buffer, file_length, filename};
}

void File::WriteAll(const std::string &filename, const char *buffer) {
  FILE *file = OPEN_FILE(filename, "w");

  int index = 0;
  int c;
  while ((c = (int)((unsigned char)buffer[index])) != '\0') {
    fputc(c, file);
    index++;
  }

  fclose(file);
}

File::FileReadResult File::ReadAllBinary(const std::string &filename) {
  FILE *file = OPEN_FILE(filename, "rb");

  fseek(file, 0, SEEK_END);
  size_t file_length = ftell(file);
  rewind(file);

  char *buffer = new char[file_length];
  fread(buffer, file_length, 1, file);
  fclose(file);
  return {buffer, file_length, filename};
}

void File::WriteAllBinary(const std::string &filename,
                          const unsigned char *buffer, size_t count) {
  FILE *file = OPEN_FILE(filename, "wb");
  fwrite(buffer, sizeof(char), count, file);
  fclose(file);
}

void File::CleanupTempFiles() {
  for (auto &filename : temp_files_) {
    int result = remove(filename.c_str());
    if (result != 0) {
      printf("Could not delete %s\n", filename.c_str());
    }
  }
}

File::FileReadResult File::BinaryToString(const unsigned char *buffer,
                                          size_t count) {
  std::string filename(std::tmpnam(nullptr));
  filename.insert(0, getenv("TEMP"));

  WriteAllBinary(filename, buffer, count);
  FileReadResult r = ReadAll(filename);

  temp_files_.push_back(filename);
  return r;
}

std::string File::ToTempFile(const unsigned char *buffer, size_t count) {
  std::string filename(std::tmpnam(nullptr));
  filename.insert(0, getenv("TEMP"));

  WriteAllBinary(filename, buffer, count);

  temp_files_.push_back(filename);
  return filename;
}

char &File::FileReadResult::operator[](int index) const { return data[index]; }