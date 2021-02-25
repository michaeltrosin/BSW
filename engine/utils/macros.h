//
// Created by Michael on 10.02.2021.
//
#pragma once

#define BIT(x) (1 << (x))

#define ARRAY_SIZE(arr) ((int) (sizeof(arr) / sizeof(*(arr))))

#define BITFIELD(enum)                                                                                                                               \
    inline enum operator|(enum a, enum b) { return static_cast<enum>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b)); }                 \
    inline bool operator&(enum a, enum b) { return static_cast<uint32_t>(a) & static_cast<uint32_t>(b); }                                    \
    inline bool operator==(enum a, enum b) { return a & b; }
