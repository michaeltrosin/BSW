//
// Created by Michael on 12.02.2021.
//

#include "test2d.h"

#include <math/color.h>

#include <core/render/renderer2d.h>

using namespace bsw;

Color rainbow;

Ref<Texture2D> at;

float rot = 0.0f;

void Test2D::on_render() {
    Renderer2D::reset_stats();

    glm::mat4 cam_view = glm::translate(glm::mat4(1.0f), glm::vec3(window_width() / 4, window_height() / 4, 0));// projection * cam
    glm::mat4 text_cam = glm::translate(glm::mat4(1.0f), glm::vec3(window_width() / 4, window_height() / 4, 0));

    Renderer2D::begin(m_projection * cam_view);
    //    Renderer2D::draw_centered_string("BSW::Sandbox", {window_width() / 2, window_height() / 2}, *FontManager::get_font("Title"), rainbow);
    //    Renderer2D::draw_centered_string("Some small games written in bsw",
    //                                     {window_width() / 2, window_height() / 2 + FontManager::default_font->get_string_height("H")},
    //                                     *FontManager::default_font, Color::violet);
    //    Renderer2D::draw_rotated_quad({0, 0, 1.0f}, {300, 300}, rot, rainbow);
    Renderer2D::draw_quad({50, 50, 0.0f}, {24, 24}, at);
    Renderer2D::end();
}

void Test2D::on_im_gui_render() {

}

void Test2D::on_event(Event &event) {
    if (event.is<WindowResizeEvent>()) {
        auto *e = dynamic_cast<WindowResizeEvent *>(&event);
        m_projection = glm::ortho(0.0f, (float) e->get_width(), (float) e->get_height(), 0.0f, -1.0f, 1.0f);
    } else if (event.is<MouseMovedEvent>()) {
        auto *e = dynamic_cast<MouseMovedEvent *>(&event);
        //        button.OnEvent(e);
    }
}

int c = 0;

void Test2D::on_update(float delta_time) {
    c++;
    rainbow.set_hsv(c, 1.0f, 1.0f);

    rot += 0.1f;
}

void Test2D::on_show() {
    Renderer2D::set_anchor_position((uint32_t)(AnchorPosition::TOP | AnchorPosition::LEFT));
    at = create_ref<Texture2D>(R"(C:\Users\Michael\Pictures\a.png)");
}
