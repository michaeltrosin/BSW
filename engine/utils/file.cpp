//
// Created by Michael on 13.02.2021.
//

#include "file.h"
#include <cstdio>

#define OPEN_FILE(name, data) fopen((name).c_str(), data)
#define OPEN_FILE_C(name, data) fopen(name, data)

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
  return {buffer, file_length};
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
  return {buffer, file_length};
}

void File::WriteAllBinary(const std::string &filename,
                          const unsigned char *buffer, size_t count) {
  FILE *file = OPEN_FILE(filename, "wb");
  fwrite(buffer, sizeof(char), count, file);
  fclose(file);
}

char &File::FileReadResult::operator[](int index) const { return data[index]; }