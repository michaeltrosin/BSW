//
// Created by Michael on 14.02.2021.
//

#pragma once

#include <bsw.h>
#include <core/render/vertex_array.h>

#include <glm/glm.hpp>

namespace bsw {
class GlRenderer {
public:
    static void init();
    static void set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

    static void set_clear_color(const glm::vec4 &color);
    static void clear();

    static void draw_indexed(const Ref<VertexArray> &vertex_array, uint32_t index_count = 0);
};
}// namespace bsw
 // sw