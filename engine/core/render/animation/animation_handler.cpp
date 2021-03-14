//
// Created by Michael on 13.03.2021.
//

#include "animation_handler.h"

#include <json.hpp>

using JSON = nlohmann::json;

bsw::AnimationHandler::AnimationHandler(const std::string &file_name) { parse_animation_file(file_name); }
bsw::AnimationHandler::~AnimationHandler() = default;
bsw::Animation::~Animation() = default;

bsw::AnimationHandler::operator Ref<Texture2D>() { return m_current_animation->m_textures[m_current_animation->m_current_index]; }

void bsw::AnimationHandler::update(float delta_time) const {
    if (m_animation_paused || !m_animation_running) return;

    m_current_animation->update(delta_time);
}

//AnimationFrameElement
//    AnimationsListElement
//AnimationData

void from_json(const JSON &j, bsw::AnimationHandler::AnimationFrameElement &afe) {
    using bsw::AnimationHandler;

    j.at("x").get_to(afe.x);
    j.at("y").get_to(afe.y);
    j.at("w").get_to(afe.w);
    j.at("h").get_to(afe.h);
}

void from_json(const JSON &j, bsw::AnimationHandler::AnimationsListElement &ale) {
    using bsw::AnimationHandler;

    j.at("name").get_to(ale.name);

    for (auto &item : j.at("frames")) {
        AnimationHandler::AnimationFrameElement element{};
        from_json(item, element);
        ale.frames.push_back(element);
    }
}

void from_json(const JSON &j, bsw::AnimationHandler::AnimationData &ad) {
    using bsw::AnimationHandler;

    j.at("fps").get_to(ad.fps);
    j.at("atlas").get_to(ad.atlas);

    for (auto &item : j.at("animations")) {
        AnimationHandler::AnimationsListElement element{};
        from_json(item, element);
        ad.animations.push_back(element);
    }
}

void bsw::AnimationHandler::parse_animation_file(const std::string &resource_path) {
    File::FileReadResult file = AssetManager::read_all(resource_path);

    AnimationData parsed;
    from_json(JSON::parse(file.data), parsed);

    m_fps = parsed.fps;
    m_texture_atlas = create_ref<Texture2D>(AssetManager::get_asset_path(parsed.atlas));
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
        LOGERROR("Error in animation: %s. NOT FOUND!", animation_name.c_str());
    }
}

void bsw::AnimationHandler::continue_animation() { m_animation_paused = false; }
void bsw::AnimationHandler::pause_animation() { m_animation_paused = true; }

void bsw::AnimationHandler::stop_animation() {
    m_animation_running = false;
    m_current_animation = nullptr;
}

bsw::Animation::Animation(Ref<bsw::Texture2D> *textures, uint32_t index_count, float max_delta)
    : m_textures(textures), m_index_count(index_count), m_max_delta(max_delta) {
    reset();
}

void bsw::Animation::update(float delta) {
    m_delta += delta;

    if (m_delta > m_max_delta) {
        m_delta = 0;

        m_current_index++;
        if (m_current_index > m_index_count) { m_current_index = 0; }
    }
}
void bsw::Animation::reset() { m_current_index = 0; }
