//
// Created by Michael on 21.03.2021.
//

#pragma once

#include <core/event/events.h>
#include <core/screen/screen.h>

#include "../game/camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GameScreen : public bsw::Screen {
public:
    void on_show() override;

    void on_render() override;
    void on_im_gui_render() override;
    void on_update(float delta_time) override;

    void on_event(bsw::Event &event) override;

private:
    Camera m_camera;
};