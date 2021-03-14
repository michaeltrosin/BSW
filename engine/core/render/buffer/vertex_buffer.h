//
// Created by Michael on 14.02.2021.
//

#pragma once

#include <core/render/buffer/buffer_layout.h>

#include <cstdint>

namespace bsw {
class VertexBuffer {
public:
    explicit VertexBuffer(uint32_t size);
    VertexBuffer(float *vertices, uint32_t size);
    ~VertexBuffer();

    /**
     * Binds the buffer
     */
    void bind() const;

    /**
     * Unbinds the buffer
     */
    void unbind() const;

    /**
     * Sets the buffer data
     * @param data
     * @param size
     */
    void set_data(const void *data, uint32_t size) const;

    /**
     * Gets the Bufferlayout
     * @return
     */
    const BufferLayout &get_layout() const { return m_layout; }

    /**
     * Sets the buffer Layout
     * @param layout
     */
    void set_layout(const BufferLayout &layout) { m_layout = layout; }

private:
    uint32_t m_buffer_id;
    BufferLayout m_layout;
};
}// namespace bsw