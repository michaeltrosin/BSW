//
// Created by Michael on 08.02.2021.
//
#pragma once

namespace bsw::mouse {
using MouseCode = unsigned short;
enum : MouseCode {
    // From glfw3.h
    BUTTON_0 = 0,
    BUTTON_1 = 1,
    BUTTON_2 = 2,
    BUTTON_3 = 3,
    BUTTON_4 = 4,
    BUTTON_5 = 5,
    BUTTON_6 = 6,
    BUTTON_7 = 7,

    BUTTONLAST = BUTTON_7,
    BUTTONLEFT = BUTTON_0,
    BUTTONRIGHT = BUTTON_1,
    BUTTONMIDDLE = BUTTON_2
};
}// namespace bsw::mouse