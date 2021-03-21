//
// Created by Michael on 21.03.2021.
//

#pragma once

#include <core/event/key_events.h>
#include <core/font/font.h>
#include <glm/glm.hpp>

class Snake {
public:
    Snake();

    enum MoveDir { LEFT, UP, DOWN, RIGHT };

    void render() const;
    void update(float delta);

    void eat_apple();
    void next_apple();

    void die();

    void on_event(bsw::Event &event);

private:
    Ref<bsw::Font> m_title;

    bool m_dead{false};
    bool m_paused{false};

    MoveDir m_move_dir = DOWN;

    glm::vec2 m_apple_pos{64, 32};

    float m_size{16};

    float m_pos_x{0};
    float m_pos_y{16};

    float m_next_update = {0};

    std::vector<glm::vec2> m_tail;

    uint32_t m_length = 1;
};
