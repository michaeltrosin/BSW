//
// Created by Michael on 23.02.2021.
//

#include "shader_storage_buffer.h"

#include <glad/glad.h>

bsw::ShaderStorageBuffer::ShaderStorageBuffer(const std::vector<glm::vec4> &vertex_array) : m_buffer_id{0} {
    glGenBuffers(1, &m_buffer_id);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_buffer_id);
    glBufferData(GL_SHADER_STORAGE_BUFFER, vertex_array.size() * sizeof(*vertex_array.data()), vertex_array.data(), GL_STATIC_DRAW);
}

void bsw::ShaderStorageBuffer::bind() const { glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_buffer_id); }
void bsw::ShaderStorageBuffer::unbind() const { glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, 0); }