//
// Created by Michael on 10.02.2021.
//
#pragma once

#ifdef _WIN64
#define PLATFORM_WIN
#define PLATFORM_64
#define FILEFORMAT_CRLF
#elif _WIN32
#define PLATFORM_WIN
#define PLATFORM_32
#define FILEFORMAT_CRLF

#elif __APPLE__
#include "TargetConditionals.h"
#if TARGET_OS_IPHONE && TARGET_IPHONE_SIMULATOR
// define something for simulator
#error "NOT SUPPORTED"
#elif TARGET_OS_IPHONE
// define something for iphone
#error "NOT SUPPORTED"
#else
#define TARGET_OS_OSX 1
// define something for OSX
#error "NOT SUPPORTED"
#endif
#elif __linux
// linux
#error "NOT SUPPORTED"
#elif __unix// all unices not caught above
// Unix
#error "NOT SUPPORTED"
#elif __posix
#error "NOT SUPPORTED"
#endif

#define BIT(x) (1 << (x))

#define BITFIELD(enum)                                                                                                                               \
    inline enum operator|(enum a, enum b) { return static_cast<enum>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b)); }                         \
    inline bool operator&(enum a, enum b) { return static_cast<uint32_t>(a) & static_cast<uint32_t>(b); }                                            \
    inline bool operator==(enum a, enum b) { return a & b; }                                                                                         \
    inline bool operator==(enum a, uint32_t b) { return (uint32_t) a & b; }

#define UMAP_CONTAINS(map, search) ((map).find(search) != (map).end())

#define PIXEL(x, y, width) ((x) + (y) * (width))