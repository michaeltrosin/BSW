//
// Created by Michael on 13.03.2021.
//

#include "animation_handler.h"

#include <json.hpp>

using json = nlohmann::json;

bsw::AnimationHandler::AnimationHandler(const std::string &file_name) : Texture2D(file_name), m_current_animation_name("") {
    parse_animation_file(file_name);
}

void bsw::AnimationHandler::bind(uint32_t slot) const { m_current_animation->bind_current(slot); }
void bsw::AnimationHandler::update(float delta_time) const {
    if (m_animation_paused || !m_animation_running) return;

    m_current_animation->update(delta_time);
}

void bsw::AnimationHandler::parse_animation_file(const std::string &file_name) {
    File::FileReadResult file = AssetManager::read_all(file_name);

    auto data = json::parse(file.data);
    uint32_t fps = data["fps"];
    std::string atlas_file(data["atlas"]);
}
void bsw::AnimationHandler::add_animation(const std::string &name, Ref<bsw::Texture2D> *textures, uint32_t fps) {}

void bsw::AnimationHandler::start_animation(std::string &animation_name, uint32_t index) {
    if (UMAP_CONTAINS(m_animations, animation_name)) {
        Ref<Animation> animation = m_animations[animation_name];
        animation->m_current_index = (uint32_t) mathf::clamp(index, 0, animation->m_index_count);

        m_current_animation = animation;
        m_current_animation_name = animation_name.c_str();

        m_animation_paused = false;
        m_animation_running = true;
    } else {
        ERROR("Error in animation: %s. NOT FOUND!", animation_name.c_str());
    }
}

void bsw::AnimationHandler::continue_animation() { m_animation_paused = false; }
void bsw::AnimationHandler::pause_animation() { m_animation_paused = true; }

void bsw::AnimationHandler::stop_animation() {
    m_animation_running = false;
    m_current_animation = nullptr;
}

bsw::AnimationHandler::~AnimationHandler() { Texture2D::~Texture2D(); }
bsw::Animation::~Animation() = default;

bsw::Animation::Animation(Ref<bsw::Texture2D> *textures, uint32_t index_count, float max_delta)
    : m_textures(textures), m_index_count(index_count), m_max_delta(max_delta) {
    reset();
}

void bsw::Animation::bind_current(uint32_t slot) { m_textures[m_current_index]->bind(slot); }

void bsw::Animation::update(float delta) {
    m_delta += delta;

    if (m_delta > m_max_delta) {
        m_delta = 0;

        m_current_index++;
        if (m_current_index > m_index_count) { m_current_index = 0; }
    }
}
void bsw::Animation::reset() { m_current_index = 0; }
