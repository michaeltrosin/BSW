//
// Created by Michael on 18.02.2021.
//

#include "color.h"

#include "mathf.h"

Color::Color() : Color(255) {}

Color::Color(int c) : Color(c, c, c) {}
Color::Color(float c) : Color(c, c, c) {}
Color::Color(uint8_t c) : Color(c, c, c) {}

Color::Color(int c, int a) : Color(c, c, c, a) {}
Color::Color(float c, float a) : Color(c, c, c, a) {}
Color::Color(uint8_t c, uint8_t a) : Color(c, c, c, a) {}

Color::Color(int r, int g, int b) : Color((uint8_t) r, (uint8_t) g, (uint8_t) b) {}
Color::Color(float r, float g, float b) : Color(r, g, b, 1.0f) {}
Color::Color(uint8_t r, uint8_t g, uint8_t b) : Color(r, g, b, (uint8_t) 255) {}

Color::Color(int r, int g, int b, int a) : Color((uint8_t) r, (uint8_t) g, (uint8_t) b, (uint8_t) a) {}
Color::Color(float r, float g, float b, float a) : m_color_data({r, g, b, a}) {}
Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    : m_color_data({(float) r / 255.0f, (float) g / 255.0f, (float) b / 255.0f, (float) a / 255.0f}) {}

void Color::set_color(uint8_t r, uint8_t g, uint8_t b) {
    m_color_data = {(float) r / 255.0f, (float) g / 255.0f, (float) b / 255.0f, m_color_data.a};
}
void Color::set_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    m_color_data = {(float) r / 255.0f, (float) g / 255.0f, (float) b / 255.0f, (float) a / 255.0f};
}
void Color::set_color(float r, float g, float b) { m_color_data = {r, g, b, m_color_data.a}; }
void Color::set_color(float r, float g, float b, float a) { m_color_data = {r, g, b, a}; }

void Color::set_r(uint8_t r) { m_color_data.r = (float) r / 255.0f; }
void Color::set_g(uint8_t g) { m_color_data.g = (float) g / 255.0f; }
void Color::set_b(uint8_t b) { m_color_data.b = (float) b / 255.0f; }
void Color::set_a(uint8_t a) { m_color_data.a = (float) a / 255.0f; }

uint8_t Color::get_r() const { return (uint8_t)(m_color_data.r * 255); }
uint8_t Color::get_g() const { return (uint8_t)(m_color_data.g * 255); }
uint8_t Color::get_b() const { return (uint8_t)(m_color_data.b * 255); }
uint8_t Color::get_a() const { return (uint8_t)(m_color_data.a * 255); }

void Color::set_r(float r) { m_color_data.r = r; }
void Color::set_g(float g) { m_color_data.g = g; }
void Color::set_b(float b) { m_color_data.b = b; }
void Color::set_a(float a) { m_color_data.a = a; }

float Color::get_rf() const { return (float) m_color_data.r; }
float Color::get_gf() const { return (float) m_color_data.g; }
float Color::get_bf() const { return (float) m_color_data.b; }
float Color::get_af() const { return (float) m_color_data.a; }

Color::operator uint32_t() const {
    uint8_t r = (uint8_t)(m_color_data.r * 255.0F) & 0xFF;
    uint8_t g = (uint8_t)(m_color_data.g * 255.0F) & 0xFF;
    uint8_t b = (uint8_t)(m_color_data.b * 255.0F) & 0xFF;
    uint8_t a = (uint8_t)(m_color_data.a * 255.0F) & 0xFF;

    return (a << 24) | (b << 16) | (g << 8) | (r << 0);
}

void Color::set_hsv(int hue, float saturation, float value) {
    hue = (hue % 360 + 360) % 360;

    float c = saturation * value;
    auto x = (float) (c * (1 - mathf::abs(fmod(hue / 60.0, 2) - 1)));
    float m = value - c;

    float r, g, b;
    if (hue >= 0 && hue < 60) {
        r = c, g = x, b = 0;
    } else if (hue >= 60 && hue < 120) {
        r = x, g = c, b = 0;
    } else if (hue >= 120 && hue < 180) {
        r = 0, g = c, b = x;
    } else if (hue >= 180 && hue < 240) {
        r = 0, g = x, b = c;
    } else if (hue >= 240 && hue < 300) {
        r = x, g = 0, b = c;
    } else {
        r = c, g = 0, b = x;
    }

    m_color_data = {(r + m), (g + m), (b + m), m_color_data.a};
}

Color Color::from_hsv(int hue, float saturation, float value) {
    Color color(255);
    color.set_hsv(hue, saturation, value);
    return color;
}

Color Color::darken() const { return shade(-25); }
Color Color::lighten() const { return shade(25); }

Color Color::shade(float percent) const {
    float r = get_r();
    float g = get_g();
    float b = get_b();

    r = (float) (r * (100 + percent) / 100);
    g = (float) (g * (100 + percent) / 100);
    b = (float) (b * (100 + percent) / 100);

    r = (r < 255) ? r : 255;
    g = (g < 255) ? g : 255;
    b = (b < 255) ? b : 255;

    return {(int) r, (int) g, (int) b, (int) get_a()};
}

Color::operator int() const { return (int) operator uint32_t(); }
Color::operator float *() { return &m_color_data.r; }

#pragma region DefaultColorValues

Color Color::medium_violet_red(199, 21, 133);      // NOLINT(cert-err58-cpp)
Color Color::deep_pink(255, 20, 147);              // NOLINT(cert-err58-cpp)
Color Color::pale_violet_red(219, 112, 147);       // NOLINT(cert-err58-cpp)
Color Color::hot_pink(255, 105, 180);              // NOLINT(cert-err58-cpp)
Color Color::light_pink(255, 182, 193);            // NOLINT(cert-err58-cpp)
Color Color::pink(255, 192, 203);                  // NOLINT(cert-err58-cpp)
Color Color::dark_red(139, 0, 0);                  // NOLINT(cert-err58-cpp)
Color Color::red(255, 0, 0);                       // NOLINT(cert-err58-cpp)
Color Color::firebrick(178, 34, 34);               // NOLINT(cert-err58-cpp)
Color Color::crimson(220, 20, 60);                 // NOLINT(cert-err58-cpp)
Color Color::indian_red(205, 92, 92);              // NOLINT(cert-err58-cpp)
Color Color::light_coral(240, 128, 128);           // NOLINT(cert-err58-cpp)
Color Color::salmon(250, 128, 114);                // NOLINT(cert-err58-cpp)
Color Color::dark_salmon(233, 150, 122);           // NOLINT(cert-err58-cpp)
Color Color::light_salmon(255, 160, 122);          // NOLINT(cert-err58-cpp)
Color Color::orange_red(255, 69, 0);               // NOLINT(cert-err58-cpp)
Color Color::tomato(255, 99, 71);                  // NOLINT(cert-err58-cpp)
Color Color::dark_orange(255, 140, 0);             // NOLINT(cert-err58-cpp)
Color Color::coral(255, 127, 80);                  // NOLINT(cert-err58-cpp)
Color Color::orange(255, 165, 0);                  // NOLINT(cert-err58-cpp)
Color Color::dark_khaki(189, 183, 107);            // NOLINT(cert-err58-cpp)
Color Color::gold(255, 215, 0);                    // NOLINT(cert-err58-cpp)
Color Color::khaki(240, 230, 140);                 // NOLINT(cert-err58-cpp)
Color Color::peach_puff(255, 218, 185);            // NOLINT(cert-err58-cpp)
Color Color::yellow(255, 255, 0);                  // NOLINT(cert-err58-cpp)
Color Color::pale_goldenrod(238, 232, 170);        // NOLINT(cert-err58-cpp)
Color Color::moccasin(255, 228, 181);              // NOLINT(cert-err58-cpp)
Color Color::papaya_whip(255, 239, 213);           // NOLINT(cert-err58-cpp)
Color Color::light_goldenrod_yellow(250, 250, 210);// NOLINT(cert-err58-cpp)
Color Color::lemon_chiffon(255, 250, 205);         // NOLINT(cert-err58-cpp)
Color Color::light_yellow(255, 255, 224);          // NOLINT(cert-err58-cpp)
Color Color::maroon(128, 0, 0);                    // NOLINT(cert-err58-cpp)
Color Color::brown(165, 42, 42);                   // NOLINT(cert-err58-cpp)
Color Color::saddle_brown(139, 69, 19);            // NOLINT(cert-err58-cpp)
Color Color::sienna(160, 82, 45);                  // NOLINT(cert-err58-cpp)
Color Color::chocolate(210, 105, 30);              // NOLINT(cert-err58-cpp)
Color Color::dark_goldenrod(184, 134, 11);         // NOLINT(cert-err58-cpp)
Color Color::peru(205, 133, 63);                   // NOLINT(cert-err58-cpp)
Color Color::rosy_brown(188, 143, 143);            // NOLINT(cert-err58-cpp)
Color Color::goldenrod(218, 165, 32);              // NOLINT(cert-err58-cpp)
Color Color::sandy_brown(244, 164, 96);            // NOLINT(cert-err58-cpp)
Color Color::tan(210, 180, 140);                   // NOLINT(cert-err58-cpp)
Color Color::burlywood(222, 184, 135);             // NOLINT(cert-err58-cpp)
Color Color::wheat(245, 222, 179);                 // NOLINT(cert-err58-cpp)
Color Color::navajo_white(255, 222, 173);          // NOLINT(cert-err58-cpp)
Color Color::bisque(255, 228, 196);                // NOLINT(cert-err58-cpp)
Color Color::blanched_almond(255, 235, 205);       // NOLINT(cert-err58-cpp)
Color Color::cornsilk(255, 248, 220);              // NOLINT(cert-err58-cpp)
Color Color::dark_green(0, 100, 0);                // NOLINT(cert-err58-cpp)
Color Color::green(0, 128, 0);                     // NOLINT(cert-err58-cpp)
Color Color::dark_olive_green(85, 107, 47);        // NOLINT(cert-err58-cpp)
Color Color::forest_green(34, 139, 34);            // NOLINT(cert-err58-cpp)
Color Color::sea_green(46, 139, 87);               // NOLINT(cert-err58-cpp)
Color Color::olive(128, 128, 0);                   // NOLINT(cert-err58-cpp)
Color Color::olive_drab(107, 142, 35);             // NOLINT(cert-err58-cpp)
Color Color::medium_sea_green(60, 179, 113);       // NOLINT(cert-err58-cpp)
Color Color::lime_green(50, 205, 50);              // NOLINT(cert-err58-cpp)
Color Color::lime(0, 255, 0);                      // NOLINT(cert-err58-cpp)
Color Color::spring_green(0, 255, 127);            // NOLINT(cert-err58-cpp)
Color Color::medium_spring_green(0, 250, 154);     // NOLINT(cert-err58-cpp)
Color Color::dark_sea_green(143, 188, 143);        // NOLINT(cert-err58-cpp)
Color Color::medium_aquamarine(102, 205, 170);     // NOLINT(cert-err58-cpp)
Color Color::yellow_green(154, 205, 50);           // NOLINT(cert-err58-cpp)
Color Color::lawn_green(124, 252, 0);              // NOLINT(cert-err58-cpp)
Color Color::chartreuse(127, 255, 0);              // NOLINT(cert-err58-cpp)
Color Color::light_green(144, 238, 144);           // NOLINT(cert-err58-cpp)
Color Color::green_yellow(173, 255, 47);           // NOLINT(cert-err58-cpp)
Color Color::pale_green(152, 251, 152);            // NOLINT(cert-err58-cpp)
Color Color::teal(0, 128, 128);                    // NOLINT(cert-err58-cpp)
Color Color::dark_cyan(0, 139, 139);               // NOLINT(cert-err58-cpp)
Color Color::light_sea_green(32, 178, 170);        // NOLINT(cert-err58-cpp)
Color Color::cadet_blue(95, 158, 160);             // NOLINT(cert-err58-cpp)
Color Color::dark_turquoise(0, 206, 209);          // NOLINT(cert-err58-cpp)
Color Color::medium_turquoise(72, 209, 204);       // NOLINT(cert-err58-cpp)
Color Color::turquoise(64, 224, 208);              // NOLINT(cert-err58-cpp)
Color Color::aqua(0, 255, 255);                    // NOLINT(cert-err58-cpp)
Color Color::cyan(0, 255, 255);                    // NOLINT(cert-err58-cpp)
Color Color::aquamarine(127, 255, 212);            // NOLINT(cert-err58-cpp)
Color Color::pale_turquoise(175, 238, 238);        // NOLINT(cert-err58-cpp)
Color Color::light_cyan(224, 255, 255);            // NOLINT(cert-err58-cpp)
Color Color::navy(0, 0, 128);                      // NOLINT(cert-err58-cpp)
Color Color::dark_blue(0, 0, 139);                 // NOLINT(cert-err58-cpp)
Color Color::medium_blue(0, 0, 205);               // NOLINT(cert-err58-cpp)
Color Color::blue(0, 0, 255);                      // NOLINT(cert-err58-cpp)
Color Color::midnight_blue(25, 25, 112);           // NOLINT(cert-err58-cpp)
Color Color::royal_blue(65, 105, 225);             // NOLINT(cert-err58-cpp)
Color Color::steel_blue(70, 130, 180);             // NOLINT(cert-err58-cpp)
Color Color::dodger_blue(30, 144, 255);            // NOLINT(cert-err58-cpp)
Color Color::deep_sky_blue(0, 191, 255);           // NOLINT(cert-err58-cpp)
Color Color::cornflower_blue(100, 149, 237);       // NOLINT(cert-err58-cpp)
Color Color::sky_blue(135, 206, 235);              // NOLINT(cert-err58-cpp)
Color Color::light_sky_blue(135, 206, 250);        // NOLINT(cert-err58-cpp)
Color Color::light_steel_blue(176, 196, 222);      // NOLINT(cert-err58-cpp)
Color Color::light_blue(173, 216, 230);            // NOLINT(cert-err58-cpp)
Color Color::powder_blue(176, 224, 230);           // NOLINT(cert-err58-cpp)
Color Color::indigo(75, 0, 130);                   // NOLINT(cert-err58-cpp)
Color Color::purple(128, 0, 128);                  // NOLINT(cert-err58-cpp)
Color Color::dark_magenta(139, 0, 139);            // NOLINT(cert-err58-cpp)
Color Color::dark_violet(148, 0, 211);             // NOLINT(cert-err58-cpp)
Color Color::dark_slate_blue(72, 61, 139);         // NOLINT(cert-err58-cpp)
Color Color::blue_violet(138, 43, 226);            // NOLINT(cert-err58-cpp)
Color Color::dark_orchid(153, 50, 204);            // NOLINT(cert-err58-cpp)
Color Color::fuchsia(255, 0, 255);                 // NOLINT(cert-err58-cpp)
Color Color::magenta(255, 0, 255);                 // NOLINT(cert-err58-cpp)
Color Color::slate_blue(106, 90, 205);             // NOLINT(cert-err58-cpp)
Color Color::medium_slate_blue(123, 104, 238);     // NOLINT(cert-err58-cpp)
Color Color::medium_orchid(186, 85, 211);          // NOLINT(cert-err58-cpp)
Color Color::medium_purple(147, 112, 219);         // NOLINT(cert-err58-cpp)
Color Color::orchid(218, 112, 214);                // NOLINT(cert-err58-cpp)
Color Color::violet(238, 130, 238);                // NOLINT(cert-err58-cpp)
Color Color::plum(221, 160, 221);                  // NOLINT(cert-err58-cpp)
Color Color::thistle(216, 191, 216);               // NOLINT(cert-err58-cpp)
Color Color::lavender(230, 230, 250);              // NOLINT(cert-err58-cpp)
Color Color::misty_rose(255, 228, 225);            // NOLINT(cert-err58-cpp)
Color Color::antique_white(250, 235, 215);         // NOLINT(cert-err58-cpp)
Color Color::linen(250, 240, 230);                 // NOLINT(cert-err58-cpp)
Color Color::beige(245, 245, 220);                 // NOLINT(cert-err58-cpp)
Color Color::white_smoke(245, 245, 245);           // NOLINT(cert-err58-cpp)
Color Color::lavender_blush(255, 240, 245);        // NOLINT(cert-err58-cpp)
Color Color::old_lace(253, 245, 230);              // NOLINT(cert-err58-cpp)
Color Color::alice_blue(240, 248, 255);            // NOLINT(cert-err58-cpp)
Color Color::seashell(255, 245, 238);              // NOLINT(cert-err58-cpp)
Color Color::ghost_white(248, 248, 255);           // NOLINT(cert-err58-cpp)
Color Color::honeydew(240, 255, 240);              // NOLINT(cert-err58-cpp)
Color Color::floral_white(255, 250, 240);          // NOLINT(cert-err58-cpp)
Color Color::azure(240, 255, 255);                 // NOLINT(cert-err58-cpp)
Color Color::mint_cream(245, 255, 250);            // NOLINT(cert-err58-cpp)
Color Color::snow(255, 250, 250);                  // NOLINT(cert-err58-cpp)
Color Color::ivory(255, 255, 240);                 // NOLINT(cert-err58-cpp)
Color Color::white(255, 255, 255);                 // NOLINT(cert-err58-cpp)
Color Color::black(0, 0, 0);                       // NOLINT(cert-err58-cpp)
Color Color::dark_slate_gray(47, 79, 79);          // NOLINT(cert-err58-cpp)
Color Color::dim_gray(105, 105, 105);              // NOLINT(cert-err58-cpp)
Color Color::slate_gray(112, 128, 144);            // NOLINT(cert-err58-cpp)
Color Color::gray(128, 128, 128);                  // NOLINT(cert-err58-cpp)
Color Color::light_slate_gray(119, 136, 153);      // NOLINT(cert-err58-cpp)
Color Color::dark_gray(169, 169, 169);             // NOLINT(cert-err58-cpp)
Color Color::silver(192, 192, 192);                // NOLINT(cert-err58-cpp)
Color Color::light_gray(211, 211, 211);            // NOLINT(cert-err58-cpp)

#pragma endregion DefaultColorValues