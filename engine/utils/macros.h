//
// Created by Michael on 10.02.2021.
//
#pragma once

#define BIT(x) (1 << (x))

#define BITFIELD(enum)                                                         \
  inline enum operator|(enum a, enum b) {                                      \
    return static_cast<enum>(static_cast<unsigned int>(a) |                    \
                             static_cast<unsigned int>(b));                    \
  }                                                                            \
  inline bool operator&(enum a, enum b) {                                      \
    return static_cast<unsigned int>(a) & static_cast<unsigned int>(b);        \
  }                                                                            \
  inline bool operator==(enum a, enum b) { return a & b; }