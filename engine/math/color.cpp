//
// Created by Michael on 18.02.2021.
//

#include "color.h"

#include <math/mathf.h>

Color Color::red(255, 0, 0);
Color Color::green(0, 255, 0);
Color Color::blue(0, 0, 255);

Color::Color() : Color(255, 255, 255, 255) {}

Color::Color(const glm::vec4 &color) : m_color_data(color) {}
Color::Color(const glm::vec3 &color) : m_color_data(color, 1.0f) {}

Color::Color(int c) : Color(c, c, c) {}
Color::Color(float c) : Color(c, c, c) {}
Color::Color(uint32_t c) : Color(c, c, c) {}

Color::Color(int c, int a) : Color(c, c, c, a) {}
Color::Color(float c, float a) : Color(c, c, c, a) {}
Color::Color(uint32_t c, uint32_t a) : Color(c, c, c, a) {}

Color::Color(int r, int g, int b) : Color((uint32_t) r, (uint32_t) g, (uint32_t) b) {}
Color::Color(float r, float g, float b) : Color(r, g, b, 1.0f) {}
Color::Color(uint32_t r, uint32_t g, uint32_t b) : Color(r, g, b, (uint32_t) 255) {}

Color::Color(int r, int g, int b, int a) : Color((uint32_t) r, (uint32_t) g, (uint32_t) b, (uint32_t) a) {}
Color::Color(float r, float g, float b, float a) : m_color_data({r, g, b, a}) {}
Color::Color(uint32_t r, uint32_t g, uint32_t b, uint32_t a) : m_color_data({r / 255.0, g / 255.0, b / 255.0, a / 255.0}) {}

void Color::set_color(const glm::vec4 &color) { m_color_data = color; }
void Color::set_color(const glm::vec3 &color) { m_color_data = {color, m_color_data.a}; }
void Color::set_color(uint32_t r, uint32_t g, uint32_t b) { m_color_data = {r / 255.0, g / 255.0, b / 255.0, m_color_data.a}; }
void Color::set_color(uint32_t r, uint32_t g, uint32_t b, uint32_t a) { m_color_data = {r / 255.0, g / 255.0, b / 255.0, a / 255.0}; }
void Color::set_color(float r, float g, float b) { m_color_data = {r, g, b, m_color_data.a}; }
void Color::set_color(float r, float g, float b, float a) { m_color_data = {r, g, b, a}; }

void Color::set_r(uint32_t r) { m_color_data.r = r / 255.0; }
void Color::set_g(uint32_t g) { m_color_data.g = g / 255.0; }
void Color::set_b(uint32_t b) { m_color_data.b = b / 255.0; }
void Color::set_a(uint32_t a) { m_color_data.a = a / 255.0; }
uint32_t Color::get_r() const { return (uint32_t)(m_color_data.r * 255); }
uint32_t Color::get_g() const { return (uint32_t)(m_color_data.g * 255); }
uint32_t Color::get_b() const { return (uint32_t)(m_color_data.b * 255); }
uint32_t Color::get_a() const { return (uint32_t)(m_color_data.a * 255); }

void Color::set_r(float r) { m_color_data.r = r; }
void Color::set_g(float g) { m_color_data.g = g; }
void Color::set_b(float b) { m_color_data.b = b; }
void Color::set_a(float a) { m_color_data.a = a; }
float Color::get_rf() const { return m_color_data.r; }
float Color::get_gf() const { return m_color_data.g; }
float Color::get_bf() const { return m_color_data.b; }
float Color::get_af() const { return m_color_data.a; }

Color::operator uint32_t() const {
    uint32_t r = (uint32_t)(m_color_data.r * 255) & 0xFF;
    uint32_t g = (uint32_t)(m_color_data.g * 255) & 0xFF;
    uint32_t b = (uint32_t)(m_color_data.b * 255) & 0xFF;
    uint32_t a = (uint32_t)(m_color_data.a * 255) & 0xFF;

    return (r << 24) | (g << 16) | (b << 8) | (a << 0);
}

void Color::set_hsv(int hue, float saturation, float value) {
    hue = (hue % 360 + 360) % 360;

    float c = saturation * value;
    auto x = (float) (c * (1 - abs(fmod(hue / 60.0, 2) - 1)));
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
    Color color(glm::vec4(1.0f));
    color.set_hsv(hue, saturation, value);
    return color;
}

Color Color::blend(Color other) const {
    float oneminusalpha = 1 - get_af();

    int newR = ((other.get_r() * other.get_af()) + (oneminusalpha * other.get_r()));
    int newG = ((other.get_g() * other.get_af()) + (oneminusalpha * other.get_g()));
    int newB = ((other.get_b() * other.get_af()) + (oneminusalpha * other.get_b()));

    return {newR, newG, newB};
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
Color::operator glm::vec4() { return m_color_data; }

Color::operator float *() { return &m_color_data.x; }
