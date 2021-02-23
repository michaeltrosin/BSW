//
// Created by Michael on 12.02.2021.
//

#pragma once

#include <core/event/events.h>
#include <core/screen/screen.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Test2D : public bsw::Screen {
public:
    void on_update(float delta_time) override;
    void on_render() override;
    void on_im_gui_render() override;
    void on_event(bsw::Event &event) override;

    void on_show() override;

private:
    glm::mat4 m_projection =
        glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f);
};
