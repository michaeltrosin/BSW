//
// Created by Michael on 18.02.2021.
//

#pragma once

#include <glm/glm.hpp>

class Color {
public:
    Color();

    // Allow implicit conversion to vec4
    Color(const glm::vec4 &color);// NOLINT(google-explicit-constructor)
    // Allow implicit conversion to vec3
    Color(const glm::vec3 &color);// NOLINT(google-explicit-constructor)

    explicit Color(uint32_t c);
    explicit Color(int c);
    explicit Color(float c);

    Color(int c, int a);
    Color(float c, float a);
    Color(uint32_t c, uint32_t a);

    Color(int r, int g, int b);
    Color(float r, float g, float b);
    Color(uint32_t r, uint32_t g, uint32_t b);

    Color(int r, int g, int b, int a);
    Color(float r, float g, float b, float a);
    Color(uint32_t r, uint32_t g, uint32_t b, uint32_t a);

    Color darken() const;
    Color lighten() const;

    Color shade(float percent) const;

    /**
     * Color format HSL - HUE Saturation Lightness
     */
    static Color from_hsv(int hue, float saturation, float value);

    void set_color(const glm::vec4 &color);
    void set_color(const glm::vec3 &color);
    void set_color(uint32_t r, uint32_t g, uint32_t b);
    void set_color(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
    void set_color(float r, float g, float b);
    void set_color(float r, float g, float b, float a);

    void set_hsv(int hue, float saturation, float value);
    //    void SetHsv(float hue, float saturation, float value);

    void set_r(uint32_t r);
    void set_g(uint32_t g);
    void set_b(uint32_t b);
    void set_a(uint32_t a);
    uint32_t get_r() const;
    uint32_t get_g() const;
    uint32_t get_b() const;
    uint32_t get_a() const;

    void set_r(float r);
    void set_g(float g);
    void set_b(float b);
    void set_a(float a);
    float get_rf() const;
    float get_gf() const;
    float get_bf() const;
    float get_af() const;

    operator uint32_t() const;// NOLINT(google-explicit-constructor)
    operator int() const;     // NOLINT(google-explicit-constructor)
    operator glm::vec4();     // NOLINT(google-explicit-constructor)

    explicit operator float *();

    static Color medium_violet_red;     // (199,  21, 133);
    static Color deep_pink;             // (255,  20, 147);
    static Color pale_violet_red;       // (219, 112, 147);
    static Color hot_pink;              // (255, 105, 180);
    static Color light_pink;            // (255, 182, 193);
    static Color pink;                  // (255, 192, 203);
    static Color dark_red;              // (139,   0,   0);
    static Color red;                   // (255,   0,   0);
    static Color firebrick;             // (178,  34,  34);
    static Color crimson;               // (220,  20,  60);
    static Color indian_red;            // (205,  92,  92);
    static Color light_coral;           // (240, 128, 128);
    static Color salmon;                // (250, 128, 114);
    static Color dark_salmon;           // (233, 150, 122);
    static Color light_salmon;          // (255, 160, 122);
    static Color orange_red;            // (255,  69,   0);
    static Color tomato;                // (255,  99,  71);
    static Color dark_orange;           // (255, 140,   0);
    static Color coral;                 // (255, 127,  80);
    static Color orange;                // (255, 165,   0);
    static Color dark_khaki;            // (189, 183, 107);
    static Color gold;                  // (255, 215,   0);
    static Color khaki;                 // (240, 230, 140);
    static Color peach_puff;            // (255, 218, 185);
    static Color yellow;                // (255, 255,   0);
    static Color pale_goldenrod;        // (238, 232, 170);
    static Color moccasin;              // (255, 228, 181);
    static Color papaya_whip;           // (255, 239, 213);
    static Color light_goldenrod_yellow;// (250, 250, 210);
    static Color lemon_chiffon;         // (255, 250, 205);
    static Color light_yellow;          // (255, 255, 224);
    static Color maroon;                // (128,   0,   0);
    static Color brown;                 // (165,  42,  42);
    static Color saddle_brown;          // (139,  69,  19);
    static Color sienna;                // (160,  82,  45);
    static Color chocolate;             // (210, 105,  30);
    static Color dark_goldenrod;        // (184, 134,  11);
    static Color peru;                  // (205, 133,  63);
    static Color rosy_brown;            // (188, 143, 143);
    static Color goldenrod;             // (218, 165,  32);
    static Color sandy_brown;           // (244, 164,  96);
    static Color tan;                   // (210, 180, 140);
    static Color burlywood;             // (222, 184, 135);
    static Color wheat;                 // (245, 222, 179);
    static Color navajo_white;          // (255, 222, 173);
    static Color bisque;                // (255, 228, 196);
    static Color blanched_almond;       // (255, 235, 205);
    static Color cornsilk;              // (255, 248, 220);
    static Color dark_green;            // (  0, 100,   0);
    static Color green;                 // (  0, 128,   0);
    static Color dark_olive_green;      // ( 85, 107,  47);
    static Color forest_green;          // ( 34, 139,  34);
    static Color sea_green;             // ( 46, 139,  87);
    static Color olive;                 // (128, 128,   0);
    static Color olive_drab;            // (107, 142,  35);
    static Color medium_sea_green;      // ( 60, 179, 113);
    static Color lime_green;            // ( 50, 205,  50);
    static Color lime;                  // (  0, 255,   0);
    static Color spring_green;          // (  0, 255, 127);
    static Color medium_spring_green;   // (  0, 250, 154);
    static Color dark_sea_green;        // (143, 188, 143);
    static Color medium_aquamarine;     // (102, 205, 170);
    static Color yellow_green;          // (154, 205,  50);
    static Color lawn_green;            // (124, 252,   0);
    static Color chartreuse;            // (127, 255,   0);
    static Color light_green;           // (144, 238, 144);
    static Color green_yellow;          // (173, 255,  47);
    static Color pale_green;            // (152, 251, 152);
    static Color teal;                  // (  0, 128, 128);
    static Color dark_cyan;             // (  0, 139, 139);
    static Color light_sea_green;       // ( 32, 178, 170);
    static Color cadet_blue;            // ( 95, 158, 160);
    static Color dark_turquoise;        // (  0, 206, 209);
    static Color medium_turquoise;      // ( 72, 209, 204);
    static Color turquoise;             // ( 64, 224, 208);
    static Color aqua;                  // (  0, 255, 255);
    static Color cyan;                  // (  0, 255, 255);
    static Color aquamarine;            // (127, 255, 212);
    static Color pale_turquoise;        // (175, 238, 238);
    static Color light_cyan;            // (224, 255, 255);
    static Color navy;                  // (  0,   0, 128);
    static Color dark_blue;             // (  0,   0, 139);
    static Color medium_blue;           // (  0,   0, 205);
    static Color blue;                  // (  0,   0, 255);
    static Color midnight_blue;         // ( 25,  25, 112);
    static Color royal_blue;            // ( 65, 105, 225);
    static Color steel_blue;            // ( 70, 130, 180);
    static Color dodger_blue;           // ( 30, 144, 255);
    static Color deep_sky_blue;         // (  0, 191, 255);
    static Color cornflower_blue;       // (100, 149, 237);
    static Color sky_blue;              // (135, 206, 235);
    static Color light_sky_blue;        // (135, 206, 250);
    static Color light_steel_blue;      // (176, 196, 222);
    static Color light_blue;            // (173, 216, 230);
    static Color powder_blue;           // (176, 224, 230);
    static Color indigo;                // ( 75,   0, 130);
    static Color purple;                // (128,   0, 128);
    static Color dark_magenta;          // (139,   0, 139);
    static Color dark_violet;           // (148,   0, 211);
    static Color dark_slate_blue;       // ( 72,  61, 139);
    static Color blue_violet;           // (138,  43, 226);
    static Color dark_orchid;           // (153,  50, 204);
    static Color fuchsia;               // (255,   0, 255);
    static Color magenta;               // (255,   0, 255);
    static Color slate_blue;            // (106,  90, 205);
    static Color medium_slate_blue;     // (123, 104, 238);
    static Color medium_orchid;         // (186,  85, 211);
    static Color medium_purple;         // (147, 112, 219);
    static Color orchid;                // (218, 112, 214);
    static Color violet;                // (238, 130, 238);
    static Color plum;                  // (221, 160, 221);
    static Color thistle;               // (216, 191, 216);
    static Color lavender;              // (230, 230, 250);
    static Color misty_rose;            // (255, 228, 225);
    static Color antique_white;         // (250, 235, 215);
    static Color linen;                 // (250, 240, 230);
    static Color beige;                 // (245, 245, 220);
    static Color white_smoke;           // (245, 245, 245);
    static Color lavender_blush;        // (255, 240, 245);
    static Color old_lace;              // (253, 245, 230);
    static Color alice_blue;            // (240, 248, 255);
    static Color seashell;              // (255, 245, 238);
    static Color ghost_white;           // (248, 248, 255);
    static Color honeydew;              // (240, 255, 240);
    static Color floral_white;          // (255, 250, 240);
    static Color azure;                 // (240, 255, 255);
    static Color mint_cream;            // (245, 255, 250);
    static Color snow;                  // (255, 250, 250);
    static Color ivory;                 // (255, 255, 240);
    static Color white;                 // (255, 255, 255);
    static Color black;                 // (  0,   0,   0);
    static Color dark_slate_gray;       // ( 47,  79,  79);
    static Color dim_gray;              // (105, 105, 105);
    static Color slate_gray;            // (112, 128, 144);
    static Color gray;                  // (128, 128, 128);
    static Color light_slate_gray;      // (119, 136, 153);
    static Color dark_gray;             // (169, 169, 169);
    static Color silver;                // (192, 192, 192);
    static Color light_gray;            // (211, 211, 211);

private:
    glm::vec4 m_color_data;
};