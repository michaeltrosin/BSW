//
// Created by Michael on 14.02.2021.
//

#pragma once

#include <cstdint>

namespace bsw {
class IndexBuffer {
public:
    IndexBuffer(uint32_t *indices, uint32_t count);
    ~IndexBuffer();

    /**
     * Binds the buffer
     */
    void bind() const;

    /**
     * Unbinds the buffer
     */
    void unbind() const;

    /**
     * Gets the element count
     * @return
     */
    uint32_t get_count() const { return m_count; }

private:
    uint32_t m_buffer_id;
    uint32_t m_count;
};
}// namespace bsw