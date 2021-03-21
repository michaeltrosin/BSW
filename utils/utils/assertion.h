//
// Created by Michael on 09.02.2021.
//
#pragma once

#include <cstdio>
#include <iostream>

#ifdef BUILD_DEBUG
#define ASSERT(x, msg)                                                                                                                               \
    do {                                                                                                                                             \
        if (!(x)) {                                                                                                                                  \
            std::cerr << "Assertion failed! '" << #x << "' at line " << __LINE__ << " in file " << __FILE__ << std::endl;                            \
            std::cerr << "Reason: '" << (msg) << "'" << std::endl;                                                                                   \
            __debugbreak();                                                                                                                          \
        }                                                                                                                                            \
    } while (0)
#define ASSERT_NO_MSG(x) ASSERT(x, "No message provided")

#define ASSERT_TYPE(type, equals) ASSERT(typeid(type) == typeid(equals), "Type mismatch!")

#define ASSERT_NOT_REACHED(msg)                                                                                                                      \
    do {                                                                                                                                             \
        std::cerr << "Reached invalid line " << __LINE__ << " in file " << __FILE__ << std::endl;                                                    \
        std::cerr << "Reason: '" << (msg) << "'" << std::endl;                                                                                       \
        __debugbreak();                                                                                                                              \
    } while (0)

#define ASSERT_NOT_REACHED_NO_MSG() ASSERT_NOT_REACHED("No message provided")
#else
#define ASSERT(x, msg)                                                                                                                               \
    std::cerr << "Assertion failed! '" << #x << "' at line " << __LINE__ << " in file " << __FILE__ << std::endl;                                    \
    std::cerr << "Message: '" << (msg) << "'" << std::endl
#define ASSERT_NOT_REACHED()
#define ASSERT_TYPE(...)
#endif
