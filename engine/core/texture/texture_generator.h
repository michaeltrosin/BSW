//
// Created by Michael on 16.03.2021.
//

#pragma once

#include <bsw.h>
#include <core/texture/texture2d.h>

namespace bsw {

class Texture2D;

class TextureGenerator {
protected:
    /**
     * Generates a texture2d based on rgba color values --> bpp = 4
     *
     * @param width
     * @param height
     * @param rgb_data
     * @return
     */
    static Ref<Texture2D> generate_texture(uint32_t width, uint32_t height, void *rgba_data);

public:
    /**
     * Generates a checkerbord texture. Used when a texture cannot be found
     * @param width
     * @param height
     * @return
     */
    static Ref<Texture2D> generate_unknown_texture();
};

}// namespace bsw