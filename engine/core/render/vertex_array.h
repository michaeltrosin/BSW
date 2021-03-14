//
// Created by Michael on 14.02.2021.
//

#pragma once

#include <bsw.h>
#include <core/render/buffer/index_buffer.h>
#include <core/render/buffer/vertex_buffer.h>

#include <vector>

namespace bsw {
class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    /**
     * Binds the array
     */
    void bind() const;

    /**
     * Unbinds the array
     */
    void unbind() const;

    /**
     * Adds a vertex buffer
     * @param vertex_buffer
     */
    void add_vertex_buffer(const Ref<VertexBuffer> &vertex_buffer);

    /**
     * Sets the index buffer
     * @param index_buffer
     */
    void set_index_buffer(const Ref<IndexBuffer> &index_buffer);

    /**
     * Get the vertex buffers
     * @return
     */
    const std::vector<Ref<VertexBuffer>> &get_vertex_buffers() const { return m_vertex_buffers; }

    /**
     * Gets the index buffer
     * @return
     */
    const Ref<bsw::IndexBuffer> &get_index_buffer() const { return m_index_buffer; }

private:
    uint32_t m_render_id;
    uint32_t m_vertex_buffer_index;

    std::vector<Ref<VertexBuffer>> m_vertex_buffers;
    Ref<IndexBuffer> m_index_buffer;
};
}// namespace bsw