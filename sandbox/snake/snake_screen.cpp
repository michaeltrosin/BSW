//
// Created by Michael on 21.03.2021.
//

#include "snake_screen.h"

#include <core/render/renderer2d.h>

using namespace bsw;

void SnakeGame::on_render() {
    Renderer2D::begin(m_projection);
    m_snake.render();
    Renderer2D::end();
}

void SnakeGame::on_update(float delta_time) { m_snake.update(delta_time); }

void SnakeGame::on_im_gui_render() {}

void SnakeGame::on_event(bsw::Event &event) { m_snake.on_event(event); }

void SnakeGame::on_show() { Renderer2D::set_anchor_position((uint32_t)(AnchorPosition::BOTTOM | AnchorPosition::LEFT)); }
