//
// Created by Michael on 21.03.2021.
//

#pragma once

#include <core/event/events.h>
#include <core/screen/screen.h>

#include "snake.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class SnakeGame : public bsw::Screen {
public:
    void on_update(float delta_time) override;
    void on_render() override;
    void on_im_gui_render() override;
    void on_event(bsw::Event &event) override;

    void on_show() override;

private:
    glm::mat4 m_projection = glm::ortho(0.0f, 64.0f * 8, 64.0f * 8, 0.0f, -1.0f, 1.0f);

    Snake m_snake;
};
