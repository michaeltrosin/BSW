//
// Created by Michael on 16.03.2021.
//

#include "texture_generator.h"

#include <math/color.h>

Ref<bsw::Texture2D> bsw::TextureGenerator::generate_texture(uint32_t width, uint32_t height, void *rgba_data) {
    Ref<Texture2D> generated = create_ref<Texture2D>(width, height);
    generated->set_data(rgba_data, width * height * COLOR_DEPTH);
    return generated;
}

Ref<bsw::Texture2D> bsw::TextureGenerator::generate_unknown_texture() {
    uint32_t size = 2;

    auto *rgba_data = new uint32_t[size * size];

    rgba_data[0] = Color::black;
    rgba_data[1] = Color::purple;
    rgba_data[2] = Color::purple;
    rgba_data[3] = Color::black;

    auto result = generate_texture(size, size, rgba_data);
    delete[] rgba_data;
    return result;
}
