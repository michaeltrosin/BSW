//
// Created by Michael on 13.03.2021.
//

#pragma once

#include <bsw.h>
#include <core/render/texture/texture2d.h>

namespace bsw {
class AnimationHandler;

class Animation {
protected:
    friend AnimationHandler;

    //TODO: Add Animation Styles:
    //      - Forward
    //      - Reverse
    //      - Loop
    //      - Bounce (Loop Forward and Backward)

    explicit Animation(Ref<Texture2D> textures[], uint32_t index_count, float max_delta);

    void update(float delta);

    void reset();

public:
    virtual ~Animation();

private:
    uint32_t m_index_count{0};

    float m_delta{0};
    float m_max_delta{0};

    uint32_t m_current_index{0};
    Ref<Texture2D> *m_textures;
};

class AnimationHandler {
public:
    explicit AnimationHandler(const std::string &resource_path);
    ~AnimationHandler();

    struct AnimationFrameElement {
        int x;
        int y;
        int w;
        int h;
    };

    struct AnimationsListElement {
        std::string name;
        std::vector<AnimationFrameElement> frames;
    };

    struct AnimationData {
        uint32_t fps;
        std::string atlas;

        std::vector<AnimationsListElement> animations;
    };

    void add_animation(const std::string &name, Ref<Texture2D> textures[], uint32_t fps);

    operator Ref<Texture2D>();// NOLINT(google-explicit-constructor)

    void update(float delta_time) const;

    void start_animation(std::string &animation_name, uint32_t index = 0);
    void continue_animation();
    void pause_animation();
    void stop_animation();

private:
    void parse_animation_file(const std::string &file_name);

private:
    Ref<Texture2D> m_texture_atlas;

    Ref<Animation> m_current_animation;
    const char *m_current_animation_name;

    uint32_t m_fps{0};

    bool m_animation_running{false};
    bool m_animation_paused{false};

    std::unordered_map<std::string, Ref<Animation>> m_animations;
};
}// namespace bsw