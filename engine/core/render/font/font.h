//
// Created by Michael on 15.02.2021.
//

#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <bsw.h>
#include <core/render/texture/texture2d.h>

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

namespace bsw {
class Font {
public:
  struct FontChar {
    Ref<Texture2D> texture;
    glm::vec2 size;
    glm::vec2 bearing;
    uint32_t advance;
  };

  explicit Font(const std::string &file_path, uint32_t font_size = 48);

  FontChar &GetFontData(char character) const;

  static Single<Font> Default;
private:
  mutable std::unordered_map<char, FontChar> characters_;

  FT_Library library_{};
  FT_Face face_{};
};
} // namespace bsw
