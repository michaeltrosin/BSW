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

    void bind() const;
    void unbind() const;

    void add_vertex_buffer(const Ref<VertexBuffer> &vertex_buffer);
    void set_index_buffer(const Ref<IndexBuffer> &index_buffer);

    const std::vector<Ref<VertexBuffer>> &get_vertex_buffers() const { return m_vertex_buffers; }
    const Ref<bsw::IndexBuffer> &get_index_buffer() const { return m_index_buffer; }

private:
    uint32_t m_render_id;
    uint32_t m_vertex_buffer_index;

    std::vector<Ref<VertexBuffer>> m_vertex_buffers;
    Ref<IndexBuffer> m_index_buffer;
};
}// namespace bsw