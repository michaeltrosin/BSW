//
// Created by Michael on 20.03.2021.
//

#pragma once

#include <bsw.h>

namespace bsw {

template<typename T>
using Resource = Ref<T>;

class Font;
class Shader;
class Texture2D;

class ResourceManager {
public:
    static Resource<Shader> load_shader(const std::string &path);
    static Resource<Texture2D> load_texture(const std::string &path);
    static Resource<Texture2D> load_texture(const std::string &path, uint32_t offx, uint32_t offy, uint32_t width, uint32_t height);
    static Resource<Font> load_font(const std::string &path, uint32_t font_size);
};
}// namespace bsw