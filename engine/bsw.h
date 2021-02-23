//
// Created by Michael on 08.02.2021.
//
#pragma once

#include <imgui/imgui.h>
#include <math/mathf.h>
#include <utils/assertion.h>
#include <utils/macros.h>

#include <cstdint>
#include <memory>

//BSW = Bitsch Succs Weiner

template<typename T>
using Single = std::unique_ptr<T>;

template<typename T, typename... Args>
constexpr Single<T> create_single(Args &&...args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T, typename... Args>
constexpr Ref<T> create_ref(Args &&...args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}