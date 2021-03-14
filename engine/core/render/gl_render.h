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
    /**
     * Initializes the renderer
     */
    static void init();

    /**
     * Updates the Viewport for opengl
     * @param x
     * @param y
     * @param width
     * @param height
     */
    static void set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

    /**
     * Sets the Clearcolor
     * @param color
     */
    static void set_clear_color(const glm::vec4 &color);

    /**
     * Clears the frame buffer for netxt draw
     */
    static void clear();

    /**
     * Draws a vertex array
     * @param vertex_array
     * @param index_count
     */
    static void draw_indexed(const Ref<VertexArray> &vertex_array, uint32_t index_count = 0);
};
}// namespace bsw
 // sw