//
// Created by Michael on 19.02.2021.
//

#pragma once

#include <bsw.h>
#include <core/event/mouse_events.h>
#include <core/font/font.h>
#include <core/render/renderer2d.h>

#include <glm/glm.hpp>
#include <string>

namespace bsw::ui {

class UiButton {
public:
    UiButton(std::string  text, const glm::vec2& pos,
             const glm::vec2& size, const glm::vec4& color);

    void Draw();

    void OnEvent(MouseMovedEvent* event);
    bool IsMouseOver() const;

    void SetColor(const glm::vec4& color);

private:
    bool mouse_over_;

    std::string text_;
    glm::vec2 pos_;
    glm::vec2 size_;
    glm::vec4 color_;
};
}// namespace bsw::ui
