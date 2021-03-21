//
// Created by Michael on 21.03.2021.
//

#include "snake.h"

#include <core/assets/resource_manager.h>
#include <core/render/renderer2d.h>

Snake::Snake() { m_title = bsw::ResourceManager::load_font("fonts\\Roboto-Light.ttf", 48); }

void Snake::render() const {
    if (m_dead) {
        bsw::Renderer2D::draw_centered_string("U ded bro...", {64 * 8 / 2, 64 * 8 / 2}, m_title, Color::orange_red);
    } else {
        if (m_paused) { bsw::Renderer2D::draw_centered_string("U paused bro...", {64 * 8 / 2, 64 * 8 / 2}, m_title, Color::green_yellow); }
        bsw::Renderer2D::draw_quad({m_pos_x, m_pos_y}, {m_size, m_size}, Color::green);
        bsw::Renderer2D::draw_quad({m_pos_x, m_pos_y}, {m_size - 2, m_size - 2}, Color::light_green);

        for (auto &tail : m_tail) { bsw::Renderer2D::draw_quad({tail.x, tail.y}, {m_size, m_size}, Color::green); }

        bsw::Renderer2D::draw_quad(m_apple_pos, {m_size, m_size}, Color::red);
    }
}

void Snake::eat_apple() {
    m_tail.emplace_back(m_pos_x, m_pos_y);
    m_length++;
}

void Snake::die() { m_dead = true; }

void Snake::update(float delta) {
    if (m_paused) return;
    if (m_dead) return;

    float speed = 60.0f / m_length / 2.0f;

    m_next_update += delta;

    if (m_next_update > speed) {
        glm::vec2 last = {m_pos_x, m_pos_y};

        if (m_apple_pos.x == m_pos_x && m_apple_pos.y == m_pos_y) {
            eat_apple();
            next_apple();
        }

        switch (m_move_dir) {
            case LEFT: m_pos_x -= m_size; break;
            case UP: m_pos_y -= m_size; break;
            case DOWN: m_pos_y += m_size; break;
            case RIGHT: m_pos_x += m_size; break;
        }

        if (m_length > 1) {
            //array back is front
            m_tail[m_length - 1] = last;

            for (uint32_t i = 0; i < m_length - 1; i++) {
                m_tail[i] = m_tail[i + 1];

                if (m_tail[i].x == m_pos_x && m_tail[i].y == m_pos_y) { die(); }
            }
        }

        m_next_update = 0;
    }
}

void Snake::on_event(bsw::Event &event) {
    if (event.is<bsw::KeyReleasedEvent>()) {
        auto *e = dynamic_cast<bsw::KeyReleasedEvent *>(&event);

        switch (e->get_key_code()) {
            case bsw::key::W:
            case bsw::key::UP: m_move_dir = UP; break;

            case bsw::key::A:
            case bsw::key::LEFT: m_move_dir = LEFT; break;

            case bsw::key::S:
            case bsw::key::DOWN: m_move_dir = DOWN; break;

            case bsw::key::D:
            case bsw::key::RIGHT: m_move_dir = RIGHT; break;

            case bsw::key::SPACE: m_paused = !m_paused; break;
        }
    }
}
void Snake::next_apple() {
    uint32_t randx = rand() % 32 + 1;
    uint32_t randy = rand() % 32 + 1;

    m_apple_pos = {randx * 16, randy * 16};
}
