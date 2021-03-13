//
// Created by Michael on 12.02.2021.
//

#pragma once

// clang-format off
#include <core/font/font.h>
#include <core/render/texture/texture2d.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <math/color.h>
#include <glm/glm.hpp>

namespace bsw {
// Batch rendering

enum class AnchorPosition : uint32_t {
    BOTTOM = BIT(0),
    TOP = BIT(1),

    LEFT = BIT(2),
    RIGHT = BIT(3),
    CENTER = BIT(4),
};

BITFIELD(AnchorPosition)

class Renderer2D {
public:
    Renderer2D() = default;
    ~Renderer2D() = default;

    static void init();
    static void shutdown();
    static void set_anchor_position(uint32_t anchor_position);

    static void begin(const glm::mat4 &view_projection);
    static void end();
    static void flush();

    struct Statistics {
        uint32_t draw_calls = 0;
        uint32_t quad_count = 0;

        uint32_t get_total_vertex_count() const { return quad_count * 4; }
        uint32_t get_total_index_count() const { return quad_count * 6; }
    };

    static void reset_stats();
    static Statistics get_stats();

    static void draw_quad(const glm::vec2 &position, const glm::vec2 &size, const Color &color);
    static void draw_quad(const glm::vec3 &position, const glm::vec2 &size, const Color &color);

    static void draw_quad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, glm::vec2 *texture_coords,
                          float tiling_factor = 1.0f, const Color &tint_color = glm::vec4(1.0f));
    static void draw_quad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, glm::vec2 *texture_coords,
                          float tiling_factor = 1.0f, const Color &tint_color = glm::vec4(1.0f));
    static void draw_quad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, float tiling_factor = 1.0f,
                          const Color &tint_color = glm::vec4(1.0f));
    static void draw_quad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, float tiling_factor = 1.0f,
                          const Color &tint_color = glm::vec4(1.0f));

    static void draw_quad(const glm::mat4 &transform, const Color &color);
    static void draw_quad(const glm::mat4 &transform, const Ref<Texture2D> &texture, float tiling_factor = 1.0f,
                          const Color &tint_color = glm::vec4(1.0f));
    static void draw_quad(const glm::mat4 &transform, const Ref<Texture2D> &texture, glm::vec2 *tex_coords, float tiling_factor = 1.0f,
                          const Color &tint_color = glm::vec4(1.0f));

    static void draw_sub_quad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, const glm::vec2 &cut_offset,
                              const glm::vec2 &cut_size, float tiling_factor = 1.0f, const Color &tint_color = glm::vec4(1.0f));
    static void draw_sub_quad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, const glm::vec2 &cut_offset,
                              const glm::vec2 &cut_size, float tiling_factor = 1.0f, const Color &tint_color = glm::vec4(1.0f));
    static void draw_sub_quad(const glm::mat4 &transform, const Ref<Texture2D> &texture, const glm::vec2 &cut_offset, const glm::vec2 &cut_size,
                              float tiling_factor = 1.0f, const Color &tint_color = glm::vec4(1.0f));

    static void draw_rotated_quad(const glm::vec2 &position, const glm::vec2 &size, float rotation, const Color &color,
                                  uint32_t anchor_position = (uint32_t) AnchorPosition::CENTER);
    static void draw_rotated_quad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const Color &color,
                                  uint32_t anchor_position = (uint32_t) AnchorPosition::CENTER);
    static void draw_rotated_quad(const glm::vec2 &position, const glm::vec2 &size, float rotation, const Ref<Texture2D> &texture,
                                  float tiling_factor = 1.0f, const Color &tint_color = glm::vec4(1.0f),
                                  uint32_t anchor_position = (uint32_t) AnchorPosition::CENTER);
    static void draw_rotated_quad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const Ref<Texture2D> &texture,
                                  float tiling_factor = 1.0f, const Color &tint_color = glm::vec4(1.0f),
                                  uint32_t anchor_position = (uint32_t) AnchorPosition::CENTER);

    //TODO: Add dynamic fontsize
    static void draw_string(const std::string &text, const glm::vec2 &position, const Font &font, const Color &text_color = glm::vec4(1.0f));
    static void draw_string(const std::string &text, const glm::vec3 &position, const Font &font, const Color &text_color = glm::vec4(1.0f));
    static void draw_centered_string(const std::string &text, const glm::vec2 &position, const Font &font, const Color &text_color = glm::vec4(1.0f));
    static void draw_centered_string(const std::string &text, const glm::vec3 &position, const Font &font, const Color &text_color = glm::vec4(1.0f));

private:
    static void start_batch();
    static void next_batch();

    static glm::vec3 perform_origin_transform(const glm::vec3 &position, const glm::vec2 &size, uint32_t anchor_position);
};
}// namespace bsw