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

    /**
     * Updates the current animation
     * @param delta
     */
    void update(float delta);

    /**
     * Resets the animation index
     */
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

    /**
     * Adds a new animation the handler
     * @param name
     * @param textures
     * @param fps
     */
    void add_animation(const std::string &name, Ref<Texture2D> textures[], uint32_t fps);

    /**
     * Returns the current animation texture
     * @return
     */
    operator Ref<Texture2D>();// NOLINT(google-explicit-constructor)

    /**
     * Updates the animation handler
     * @param delta_time
     */
    void update(float delta_time) const;

    /**
     * Starts a animation with a given name
     * @param animation_name
     * @param index
     */
    void start_animation(std::string &animation_name, uint32_t index = 0);

    /**
     * Continues the current paused animation
     */
    void continue_animation();

    /**
     * Pauses the current animation
     */
    void pause_animation();

    /**
     * Stops the current animation
     */
    void stop_animation();

private:
    /**
     * Parses a given animation file
     * @param file_name
     */
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