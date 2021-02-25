//
// Created by Michael on 12.02.2021.
//

#include "test2d.h"

#include <core/font/font_manager.h>
#include <core/render/renderer2d.h>
#include <engine.h>
#include <math/color.h>
#include <ui_button.h>

#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace bsw;
using namespace ui;

Color rainbow;

Ref<Texture2D> at;

float rot = 0.0f;

void Test2D::on_render() {
    Renderer2D::reset_stats();

    glm::mat4 cam_view = glm::translate(glm::mat4(1.0f), glm::vec3(window_width() / 4, window_height() / 4, 0));// projection * cam

    glm::mat4 text_cam = glm::translate(glm::mat4(1.0f), glm::vec3(window_width() / 4, window_height() / 4, 0));

//    Renderer2D::begin(m_projection);
////    Renderer2D::draw_quad({250, 250, 0.0f}, {300, 300}, {1.0f, 0.0f, 0.0f, 0.7f});
////    Renderer2D::draw_quad({200, 200, 0.0f}, {900, 900}, {1.0f, 0.0f, 0.0f, 0.5f});
//    Renderer2D::end();

    Renderer2D::begin(m_projection);
    //    Renderer2D::draw_centered_string("BSW::Sandbox",
    //                                     {window_width() / 2, window_height() / 2},
    //                                     *FontManager::get_font("Title"), white.darken());
    Renderer2D::draw_centered_string("Some small games written in bsw",
                                     {window_width() / 2, window_height() / 2 + FontManager::default_font->get_string_height("H")},
                                     *FontManager::default_font, Color::violet);
    Renderer2D::draw_rotated_quad({250, 250, 1.0f}, {300, 300}, rot, at, 0.5f);
    Renderer2D::end();
}

void Test2D::on_im_gui_render() {
    ImGui::Begin("Debug");

    auto stats = Renderer2D::get_stats();
    ImGui::Text("Renderer2D Stats:");
    ImGui::Text("Draw Calls: %d", stats.draw_calls);
    ImGui::Text("Quads: %d", stats.quad_count);
    ImGui::Text("Vertices: %d", stats.get_total_vertex_count());
    ImGui::Text("Indices: %d", stats.get_total_index_count());
    ImGui::End();

    //    ImGui::Begin("Testing", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    //    ImGui::DragFloat4("Tint", &colortint.x, 0.01f, 0.0f, 1.0f);
    //    ImGui::End();1
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

    //    if (button.IsMouseOver()) {
    //        button.SetColor(Color::red);
    //    } else {
    //        button.SetColor(glm::vec4(1.0f));
    //    }

    rot += 0.1f;
}
void Test2D::on_show() { at = create_ref<Texture2D>(R"(C:\Users\Michael\Pictures\a.png)"); }
