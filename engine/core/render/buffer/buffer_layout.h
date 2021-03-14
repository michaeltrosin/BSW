//
// Created by Michael on 14.02.2021.
//

#pragma once

#include <bsw.h>

#include <utility>
#include <vector>

namespace bsw {
enum class ShaderDataType : uint32_t { NONE = 0, FLOAT, FLOAT_2, FLOAT_3, FLOAT_4, MAT_3, MAT_4, INT, INT_2, INT_3, INT_4, BOOL };

/**
 * Parses a ShaderDataType to the type size
 * @param type
 * @return
 */
static uint32_t shader_data_type_size(ShaderDataType type) {
    switch (type) {
        case ShaderDataType::FLOAT: return 4;
        case ShaderDataType::FLOAT_2: return 4 * 2;
        case ShaderDataType::FLOAT_3: return 4 * 3;
        case ShaderDataType::FLOAT_4: return 4 * 4;
        case ShaderDataType::MAT_3: return 4 * 3 * 3;
        case ShaderDataType::MAT_4: return 4 * 4 * 4;
        case ShaderDataType::INT: return 4;
        case ShaderDataType::INT_2: return 4 * 2;
        case ShaderDataType::INT_3: return 4 * 3;
        case ShaderDataType::INT_4: return 4 * 4;
        case ShaderDataType::BOOL: return 1;
        default: break;
    }

    ASSERT(false, "Unknown ShaderDataType!");
    return 0;
}

struct BufferElement {
    std::string name;
    ShaderDataType type;
    uint32_t size;
    size_t offset;
    bool normalized;

    BufferElement(ShaderDataType type, std::string name, bool normalized = false)
        : name(std::move(name)), type(type), size(shader_data_type_size(type)), offset(0), normalized(normalized) {}

    /**
     * Gets the component count of the current Element
     * @return
     */
    uint32_t get_component_count() const {
        switch (type) {
            case ShaderDataType::FLOAT: return 1;
            case ShaderDataType::FLOAT_2: return 2;
            case ShaderDataType::FLOAT_3: return 3;
            case ShaderDataType::FLOAT_4: return 4;
            case ShaderDataType::MAT_3: return 3;// 3* float3
            case ShaderDataType::MAT_4: return 4;// 4* float4
            case ShaderDataType::INT: return 1;
            case ShaderDataType::INT_2: return 2;
            case ShaderDataType::INT_3: return 3;
            case ShaderDataType::INT_4: return 4;
            case ShaderDataType::BOOL: return 1;
            default: break;
        }

        ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }
};

class BufferLayout {
public:
    BufferLayout() = default;

    BufferLayout(std::initializer_list<BufferElement> elements) : m_elements(elements) { calculate_offsets_and_stride(); }

    /**
     * Gets the stride
     * @return
     */
    uint32_t get_stride() const { return m_stride; }

    /**
     * Gets all elements
     * @return
     */
    const std::vector<BufferElement> &get_elements() const { return m_elements; }

    std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
    std::vector<BufferElement>::iterator end() { return m_elements.end(); }
    std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
    std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }

private:
    /**
     * Calculates all offsets and strides of all elements
     */
    void calculate_offsets_and_stride() {
        size_t offset = 0;
        m_stride = 0;
        for (auto &element : m_elements) {
            element.offset = offset;
            offset += element.size;
            m_stride += element.size;
        }
    }

private:
    std::vector<BufferElement> m_elements{};
    uint32_t m_stride = 0;
};
}// namespace bsw