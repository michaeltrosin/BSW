//
// Created by Michael on 15.02.2021.
//

#include "font.h"

namespace bsw {
Single<Font> Font::Default;

Font::Font(const std::string &file_path, uint32_t font_size) {
  if (FT_Init_FreeType(&library_)) {
    ASSERT_NOT_REACHED("Font Library not initialized!");
  }

  if (FT_New_Face(library_, file_path.c_str(), 0, &face_)) {
    ASSERT_NOT_REACHED("Font not initialized!");
  }

  FT_Set_Pixel_Sizes(face_, 0, font_size);

  //  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  for (GLubyte c = 0; c < 128; c++) {
    if (FT_Load_Char(face_, c, FT_LOAD_RENDER)) {
      std::cerr << "Could not load Glyph '" << c << "'" << std::endl;
      continue;
    }
    uint32_t bmpwidth = face_->glyph->bitmap.width;
    uint32_t bmpheight = face_->glyph->bitmap.rows;

    Ref<Texture2D> texture =
        CreateRef<Texture2D>(bmpwidth, bmpheight, GL_CLAMP_TO_EDGE, GL_R8, GL_RED);

    texture->SetData(face_->glyph->bitmap.buffer,
                     8 * bmpwidth * bmpheight);

    FontChar font_char = {
        texture,
        {face_->glyph->bitmap.width, face_->glyph->bitmap.rows},
        {face_->glyph->bitmap_left, face_->glyph->bitmap_top},
        (uint32_t)face_->glyph->advance.x};

    characters_[c] = font_char;
  }

  FT_Done_Face(face_);
  FT_Done_FreeType(library_);
}

Font::FontChar &Font::GetFontData(char character) const {
  return characters_[character];
}

} // namespace bsw