//
// Created by Michael on 08.02.2021.
//
#pragma once

#include <core/assets/asset_manager.h>
#include <imgui/imgui.h>
#include <math/mathf.h>
#include <utils/assertion.h>
#include <utils/logging.h>
#include <utils/macros.h>

#include <cstdint>
#include <memory>

template<typename T>
using Scoped = std::unique_ptr<T>;

/**
 * Creates a scope based pointer
 *
 * @tparam T
 * @tparam Args
 * @param args
 * @return
 */
template<typename T, typename... Args>
constexpr Scoped<T> create_scoped(Args &&...args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using Ref = std::shared_ptr<T>;

/**
 * Creates a copyable reference counted pointer
 *
 * @tparam T
 * @tparam Args
 * @param args
 * @return
 */
template<typename T, typename... Args>
constexpr Ref<T> create_ref(Args &&...args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}