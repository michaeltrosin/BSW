//
// Created by Michael on 19.02.2021.
//

#include "ui_button.h"

#include <core/font/font_manager.h>

bsw::ui::UiButton::UiButton(std::string text, const glm::vec2& pos,
                            const glm::vec2& size, const glm::vec4& color)
    : text_(std::move(text)),
      pos_(pos),
      size_(size),
      color_(color),
      mouse_over_(false) {}

void bsw::ui::UiButton::Draw() {
    glm::vec2 textpos = pos_;
    textpos.y += size_.y / 2 - 4;

    Renderer2D::draw_centered_string(text_, textpos,
                                     *FontManager::default_font);
    Renderer2D::draw_quad(pos_, size_, color_);
}

void bsw::ui::UiButton::OnEvent(bsw::MouseMovedEvent* event) {
    float mx = event->get_x();
    float my = event->get_y();

    float minx = pos_.x - size_.x / 2;
    float miny = pos_.y - size_.y / 2;

    mouse_over_ = false;
    if (mx > minx && mx < minx + size_.x) {
        if (my > miny && my < miny + size_.y) { mouse_over_ = true; }
    }
}

bool bsw::ui::UiButton::IsMouseOver() const { return mouse_over_; }
void bsw::ui::UiButton::SetColor(const glm::vec4& color) { color_ = color; }
