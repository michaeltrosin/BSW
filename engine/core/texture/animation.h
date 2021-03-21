//
// Created by Michael on 20.03.2021.
//

#pragma once

#include <core/texture/texture2d.h>

namespace bsw {
class Animation {
public:
    operator Ref<Texture2D>();

private:
    uint32_t m_image_count;
    uint32_t m_current_index;

    Ref<Texture2D> m_current_texture;
};
}// namespace bsw