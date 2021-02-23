//
// Created by Michael on 08.02.2021.
//
#pragma once

namespace bsw::key {
using KeyCode = unsigned short;
enum : KeyCode {
    // From glfw3.h
    SPACE = 32,
    APOSTROPHE = 39, /* ' */
    COMMA = 44,      /* , */
    MINUS = 45,      /* - */
    PERIOD = 46,     /* . */
    SLASH = 47,      /* / */

    D_0 = 48, /* 0 */
    D_1 = 49, /* 1 */
    D_2 = 50, /* 2 */
    D_3 = 51, /* 3 */
    D_4 = 52, /* 4 */
    D_5 = 53, /* 5 */
    D_6 = 54, /* 6 */
    D_7 = 55, /* 7 */
    D_8 = 56, /* 8 */
    D_9 = 57, /* 9 */

    SEMICOLON = 59, /* ; */
    EQUAL = 61,     /* = */

    A = 65,
    B = 66,
    C = 67,
    D = 68,
    E = 69,
    F = 70,
    G = 71,
    H = 72,
    I = 73,
    J = 74,
    K = 75,
    L = 76,
    M = 77,
    N = 78,
    O = 79,
    P = 80,
    Q = 81,
    R = 82,
    S = 83,
    T = 84,
    U = 85,
    V = 86,
    W = 87,
    X = 88,
    Y = 89,
    Z = 90,

    LEFTBRACKET = 91,  /* [ */
    BACKSLASH = 92,    /* \ */
    RIGHTBRACKET = 93, /* ] */
    GRAVEACCENT = 96,  /* ` */

    WORLD_1 = 161, /* non-US #1 */
    WORLD_2 = 162, /* non-US #2 */

    /* Function keys */
    ESCAPE = 256,
    ENTER = 257,
    TAB = 258,
    BACKSPACE = 259,
    INSERT = 260,
    DELETE = 261,
    RIGHT = 262,
    LEFT = 263,
    DOWN = 264,
    UP = 265,
    PAGEUP = 266,
    PAGEDOWN = 267,
    HOME = 268,
    END = 269,
    CAPSLOCK = 280,
    SCROLLLOCK = 281,
    NUMLOCK = 282,
    PRINTSCREEN = 283,
    PAUSE = 284,
    F_1 = 290,
    F_2 = 291,
    F_3 = 292,
    F_4 = 293,
    F_5 = 294,
    F_6 = 295,
    F_7 = 296,
    F_8 = 297,
    F_9 = 298,
    F_10 = 299,
    F_11 = 300,
    F_12 = 301,
    F_13 = 302,
    F_14 = 303,
    F_15 = 304,
    F_16 = 305,
    F_17 = 306,
    F_18 = 307,
    F_19 = 308,
    F_20 = 309,
    F_21 = 310,
    F_22 = 311,
    F_23 = 312,
    F_24 = 313,
    F_25 = 314,

    /* Keypad */
    KP_0 = 320,
    KP_1 = 321,
    KP_2 = 322,
    KP_3 = 323,
    KP_4 = 324,
    KP_5 = 325,
    KP_6 = 326,
    KP_7 = 327,
    KP_8 = 328,
    KP_9 = 329,
    KPDECIMAL = 330,
    KPDIVIDE = 331,
    KPMULTIPLY = 332,
    KPSUBTRACT = 333,
    KPADD = 334,
    KPENTER = 335,
    KPEQUAL = 336,

    LEFTSHIFT = 340,
    LEFTCONTROL = 341,
    LEFTALT = 342,
    LEFTSUPER = 343,
    RIGHTSHIFT = 344,
    RIGHTCONTROL = 345,
    RIGHTALT = 346,
    RIGHTSUPER = 347,
    MENU = 348
};
}// namespace bsw::key
