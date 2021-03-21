//
// Created by Michael on 18.02.2021.
//

#pragma once

#include <cstdint>

#define COLOR_DEPTH 4

/**
 * If you want other color value sorting, override the exisitng COLOR_BIT_FORMAT
 *
 * #define COLOR_BIT_FORMAT
 */
class Color {
public:
    Color();

    explicit Color(uint8_t c);
    explicit Color(int c);
    explicit Color(float c);

    Color(int c, int a);
    Color(float c, float a);
    Color(uint8_t c, uint8_t a);

    Color(int r, int g, int b);
    Color(float r, float g, float b);
    Color(uint8_t r, uint8_t g, uint8_t b);

    Color(int r, int g, int b, int a);
    Color(float r, float g, float b, float a);
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    Color darken() const;
    Color lighten() const;

    Color shade(float percent) const;

    /**
     * Color format HSL - HUE Saturation Lightness
     */
    static Color from_hsv(int hue, float saturation, float value);

    void set_color(uint8_t r, uint8_t g, uint8_t b);
    void set_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void set_color(float r, float g, float b);
    void set_color(float r, float g, float b, float a);

    void set_hsv(int hue, float saturation, float value);
    //    void SetHsv(float hue, float saturation, float value);

    void set_r(uint8_t r);
    void set_g(uint8_t g);
    void set_b(uint8_t b);
    void set_a(uint8_t a);
    uint8_t get_r() const;
    uint8_t get_g() const;
    uint8_t get_b() const;
    uint8_t get_a() const;

    void set_r(float r);
    void set_g(float g);
    void set_b(float b);
    void set_a(float a);

    float get_rf() const;
    float get_gf() const;
    float get_bf() const;
    float get_af() const;

    /**
     * Returns the color as ABGR format
     * @return
     */
    operator uint32_t() const;// NOLINT(google-explicit-constructor)
    operator int() const;     // NOLINT(google-explicit-constructor)
    explicit operator float *();

private:
    struct {
        float r;
        float g;
        float b;
        float a;
    } m_color_data;

public:
#pragma region DefaultColorValues

    [[maybe_unused]] static Color medium_violet_red;     // Value data: (R, G, B) (199,  21, 133);
    [[maybe_unused]] static Color deep_pink;             // Value data: (R, G, B) (255,  20, 147);
    [[maybe_unused]] static Color pale_violet_red;       // Value data: (R, G, B) (219, 112, 147);
    [[maybe_unused]] static Color hot_pink;              // Value data: (R, G, B) (255, 105, 180);
    [[maybe_unused]] static Color light_pink;            // Value data: (R, G, B) (255, 182, 193);
    [[maybe_unused]] static Color pink;                  // Value data: (R, G, B) (255, 192, 203);
    [[maybe_unused]] static Color dark_red;              // Value data: (R, G, B) (139,   0,   0);
    [[maybe_unused]] static Color red;                   // Value data: (R, G, B) (255,   0,   0);
    [[maybe_unused]] static Color firebrick;             // Value data: (R, G, B) (178,  34,  34);
    [[maybe_unused]] static Color crimson;               // Value data: (R, G, B) (220,  20,  60);
    [[maybe_unused]] static Color indian_red;            // Value data: (R, G, B) (205,  92,  92);
    [[maybe_unused]] static Color light_coral;           // Value data: (R, G, B) (240, 128, 128);
    [[maybe_unused]] static Color salmon;                // Value data: (R, G, B) (250, 128, 114);
    [[maybe_unused]] static Color dark_salmon;           // Value data: (R, G, B) (233, 150, 122);
    [[maybe_unused]] static Color light_salmon;          // Value data: (R, G, B) (255, 160, 122);
    [[maybe_unused]] static Color orange_red;            // Value data: (R, G, B) (255,  69,   0);
    [[maybe_unused]] static Color tomato;                // Value data: (R, G, B) (255,  99,  71);
    [[maybe_unused]] static Color dark_orange;           // Value data: (R, G, B) (255, 140,   0);
    [[maybe_unused]] static Color coral;                 // Value data: (R, G, B) (255, 127,  80);
    [[maybe_unused]] static Color orange;                // Value data: (R, G, B) (255, 165,   0);
    [[maybe_unused]] static Color dark_khaki;            // Value data: (R, G, B) (189, 183, 107);
    [[maybe_unused]] static Color gold;                  // Value data: (R, G, B) (255, 215,   0);
    [[maybe_unused]] static Color khaki;                 // Value data: (R, G, B) (240, 230, 140);
    [[maybe_unused]] static Color peach_puff;            // Value data: (R, G, B) (255, 218, 185);
    [[maybe_unused]] static Color yellow;                // Value data: (R, G, B) (255, 255,   0);
    [[maybe_unused]] static Color pale_goldenrod;        // Value data: (R, G, B) (238, 232, 170);
    [[maybe_unused]] static Color moccasin;              // Value data: (R, G, B) (255, 228, 181);
    [[maybe_unused]] static Color papaya_whip;           // Value data: (R, G, B) (255, 239, 213);
    [[maybe_unused]] static Color light_goldenrod_yellow;// Value data: (R, G, B) (250, 250, 210);
    [[maybe_unused]] static Color lemon_chiffon;         // Value data: (R, G, B) (255, 250, 205);
    [[maybe_unused]] static Color light_yellow;          // Value data: (R, G, B) (255, 255, 224);
    [[maybe_unused]] static Color maroon;                // Value data: (R, G, B) (128,   0,   0);
    [[maybe_unused]] static Color brown;                 // Value data: (R, G, B) (165,  42,  42);
    [[maybe_unused]] static Color saddle_brown;          // Value data: (R, G, B) (139,  69,  19);
    [[maybe_unused]] static Color sienna;                // Value data: (R, G, B) (160,  82,  45);
    [[maybe_unused]] static Color chocolate;             // Value data: (R, G, B) (210, 105,  30);
    [[maybe_unused]] static Color dark_goldenrod;        // Value data: (R, G, B) (184, 134,  11);
    [[maybe_unused]] static Color peru;                  // Value data: (R, G, B) (205, 133,  63);
    [[maybe_unused]] static Color rosy_brown;            // Value data: (R, G, B) (188, 143, 143);
    [[maybe_unused]] static Color goldenrod;             // Value data: (R, G, B) (218, 165,  32);
    [[maybe_unused]] static Color sandy_brown;           // Value data: (R, G, B) (244, 164,  96);
    [[maybe_unused]] static Color tan;                   // Value data: (R, G, B) (210, 180, 140);
    [[maybe_unused]] static Color burlywood;             // Value data: (R, G, B) (222, 184, 135);
    [[maybe_unused]] static Color wheat;                 // Value data: (R, G, B) (245, 222, 179);
    [[maybe_unused]] static Color navajo_white;          // Value data: (R, G, B) (255, 222, 173);
    [[maybe_unused]] static Color bisque;                // Value data: (R, G, B) (255, 228, 196);
    [[maybe_unused]] static Color blanched_almond;       // Value data: (R, G, B) (255, 235, 205);
    [[maybe_unused]] static Color cornsilk;              // Value data: (R, G, B) (255, 248, 220);
    [[maybe_unused]] static Color dark_green;            // Value data: (R, G, B) (  0, 100,   0);
    [[maybe_unused]] static Color green;                 // Value data: (R, G, B) (  0, 128,   0);
    [[maybe_unused]] static Color dark_olive_green;      // Value data: (R, G, B) ( 85, 107,  47);
    [[maybe_unused]] static Color forest_green;          // Value data: (R, G, B) ( 34, 139,  34);
    [[maybe_unused]] static Color sea_green;             // Value data: (R, G, B) ( 46, 139,  87);
    [[maybe_unused]] static Color olive;                 // Value data: (R, G, B) (128, 128,   0);
    [[maybe_unused]] static Color olive_drab;            // Value data: (R, G, B) (107, 142,  35);
    [[maybe_unused]] static Color medium_sea_green;      // Value data: (R, G, B) ( 60, 179, 113);
    [[maybe_unused]] static Color lime_green;            // Value data: (R, G, B) ( 50, 205,  50);
    [[maybe_unused]] static Color lime;                  // Value data: (R, G, B) (  0, 255,   0);
    [[maybe_unused]] static Color spring_green;          // Value data: (R, G, B) (  0, 255, 127);
    [[maybe_unused]] static Color medium_spring_green;   // Value data: (R, G, B) (  0, 250, 154);
    [[maybe_unused]] static Color dark_sea_green;        // Value data: (R, G, B) (143, 188, 143);
    [[maybe_unused]] static Color medium_aquamarine;     // Value data: (R, G, B) (102, 205, 170);
    [[maybe_unused]] static Color yellow_green;          // Value data: (R, G, B) (154, 205,  50);
    [[maybe_unused]] static Color lawn_green;            // Value data: (R, G, B) (124, 252,   0);
    [[maybe_unused]] static Color chartreuse;            // Value data: (R, G, B) (127, 255,   0);
    [[maybe_unused]] static Color light_green;           // Value data: (R, G, B) (144, 238, 144);
    [[maybe_unused]] static Color green_yellow;          // Value data: (R, G, B) (173, 255,  47);
    [[maybe_unused]] static Color pale_green;            // Value data: (R, G, B) (152, 251, 152);
    [[maybe_unused]] static Color teal;                  // Value data: (R, G, B) (  0, 128, 128);
    [[maybe_unused]] static Color dark_cyan;             // Value data: (R, G, B) (  0, 139, 139);
    [[maybe_unused]] static Color light_sea_green;       // Value data: (R, G, B) ( 32, 178, 170);
    [[maybe_unused]] static Color cadet_blue;            // Value data: (R, G, B) ( 95, 158, 160);
    [[maybe_unused]] static Color dark_turquoise;        // Value data: (R, G, B) (  0, 206, 209);
    [[maybe_unused]] static Color medium_turquoise;      // Value data: (R, G, B) ( 72, 209, 204);
    [[maybe_unused]] static Color turquoise;             // Value data: (R, G, B) ( 64, 224, 208);
    [[maybe_unused]] static Color aqua;                  // Value data: (R, G, B) (  0, 255, 255);
    [[maybe_unused]] static Color cyan;                  // Value data: (R, G, B) (  0, 255, 255);
    [[maybe_unused]] static Color aquamarine;            // Value data: (R, G, B) (127, 255, 212);
    [[maybe_unused]] static Color pale_turquoise;        // Value data: (R, G, B) (175, 238, 238);
    [[maybe_unused]] static Color light_cyan;            // Value data: (R, G, B) (224, 255, 255);
    [[maybe_unused]] static Color navy;                  // Value data: (R, G, B) (  0,   0, 128);
    [[maybe_unused]] static Color dark_blue;             // Value data: (R, G, B) (  0,   0, 139);
    [[maybe_unused]] static Color medium_blue;           // Value data: (R, G, B) (  0,   0, 205);
    [[maybe_unused]] static Color blue;                  // Value data: (R, G, B) (  0,   0, 255);
    [[maybe_unused]] static Color midnight_blue;         // Value data: (R, G, B) ( 25,  25, 112);
    [[maybe_unused]] static Color royal_blue;            // Value data: (R, G, B) ( 65, 105, 225);
    [[maybe_unused]] static Color steel_blue;            // Value data: (R, G, B) ( 70, 130, 180);
    [[maybe_unused]] static Color dodger_blue;           // Value data: (R, G, B) ( 30, 144, 255);
    [[maybe_unused]] static Color deep_sky_blue;         // Value data: (R, G, B) (  0, 191, 255);
    [[maybe_unused]] static Color cornflower_blue;       // Value data: (R, G, B) (100, 149, 237);
    [[maybe_unused]] static Color sky_blue;              // Value data: (R, G, B) (135, 206, 235);
    [[maybe_unused]] static Color light_sky_blue;        // Value data: (R, G, B) (135, 206, 250);
    [[maybe_unused]] static Color light_steel_blue;      // Value data: (R, G, B) (176, 196, 222);
    [[maybe_unused]] static Color light_blue;            // Value data: (R, G, B) (173, 216, 230);
    [[maybe_unused]] static Color powder_blue;           // Value data: (R, G, B) (176, 224, 230);
    [[maybe_unused]] static Color indigo;                // Value data: (R, G, B) ( 75,   0, 130);
    [[maybe_unused]] static Color purple;                // Value data: (R, G, B) (128,   0, 128);
    [[maybe_unused]] static Color dark_magenta;          // Value data: (R, G, B) (139,   0, 139);
    [[maybe_unused]] static Color dark_violet;           // Value data: (R, G, B) (148,   0, 211);
    [[maybe_unused]] static Color dark_slate_blue;       // Value data: (R, G, B) ( 72,  61, 139);
    [[maybe_unused]] static Color blue_violet;           // Value data: (R, G, B) (138,  43, 226);
    [[maybe_unused]] static Color dark_orchid;           // Value data: (R, G, B) (153,  50, 204);
    [[maybe_unused]] static Color fuchsia;               // Value data: (R, G, B) (255,   0, 255);
    [[maybe_unused]] static Color magenta;               // Value data: (R, G, B) (255,   0, 255);
    [[maybe_unused]] static Color slate_blue;            // Value data: (R, G, B) (106,  90, 205);
    [[maybe_unused]] static Color medium_slate_blue;     // Value data: (R, G, B) (123, 104, 238);
    [[maybe_unused]] static Color medium_orchid;         // Value data: (R, G, B) (186,  85, 211);
    [[maybe_unused]] static Color medium_purple;         // Value data: (R, G, B) (147, 112, 219);
    [[maybe_unused]] static Color orchid;                // Value data: (R, G, B) (218, 112, 214);
    [[maybe_unused]] static Color violet;                // Value data: (R, G, B) (238, 130, 238);
    [[maybe_unused]] static Color plum;                  // Value data: (R, G, B) (221, 160, 221);
    [[maybe_unused]] static Color thistle;               // Value data: (R, G, B) (216, 191, 216);
    [[maybe_unused]] static Color lavender;              // Value data: (R, G, B) (230, 230, 250);
    [[maybe_unused]] static Color misty_rose;            // Value data: (R, G, B) (255, 228, 225);
    [[maybe_unused]] static Color antique_white;         // Value data: (R, G, B) (250, 235, 215);
    [[maybe_unused]] static Color linen;                 // Value data: (R, G, B) (250, 240, 230);
    [[maybe_unused]] static Color beige;                 // Value data: (R, G, B) (245, 245, 220);
    [[maybe_unused]] static Color white_smoke;           // Value data: (R, G, B) (245, 245, 245);
    [[maybe_unused]] static Color lavender_blush;        // Value data: (R, G, B) (255, 240, 245);
    [[maybe_unused]] static Color old_lace;              // Value data: (R, G, B) (253, 245, 230);
    [[maybe_unused]] static Color alice_blue;            // Value data: (R, G, B) (240, 248, 255);
    [[maybe_unused]] static Color seashell;              // Value data: (R, G, B) (255, 245, 238);
    [[maybe_unused]] static Color ghost_white;           // Value data: (R, G, B) (248, 248, 255);
    [[maybe_unused]] static Color honeydew;              // Value data: (R, G, B) (240, 255, 240);
    [[maybe_unused]] static Color floral_white;          // Value data: (R, G, B) (255, 250, 240);
    [[maybe_unused]] static Color azure;                 // Value data: (R, G, B) (240, 255, 255);
    [[maybe_unused]] static Color mint_cream;            // Value data: (R, G, B) (245, 255, 250);
    [[maybe_unused]] static Color snow;                  // Value data: (R, G, B) (255, 250, 250);
    [[maybe_unused]] static Color ivory;                 // Value data: (R, G, B) (255, 255, 240);
    [[maybe_unused]] static Color white;                 // Value data: (R, G, B) (255, 255, 255);
    [[maybe_unused]] static Color black;                 // Value data: (R, G, B) (  0,   0,   0);
    [[maybe_unused]] static Color dark_slate_gray;       // Value data: (R, G, B) ( 47,  79,  79);
    [[maybe_unused]] static Color dim_gray;              // Value data: (R, G, B) (105, 105, 105);
    [[maybe_unused]] static Color slate_gray;            // Value data: (R, G, B) (112, 128, 144);
    [[maybe_unused]] static Color gray;                  // Value data: (R, G, B) (128, 128, 128);
    [[maybe_unused]] static Color light_slate_gray;      // Value data: (R, G, B) (119, 136, 153);
    [[maybe_unused]] static Color dark_gray;             // Value data: (R, G, B) (169, 169, 169);
    [[maybe_unused]] static Color silver;                // Value data: (R, G, B) (192, 192, 192);
    [[maybe_unused]] static Color light_gray;            // Value data: (R, G, B) (211, 211, 211);

#pragma endregion DefaultColorValues
};