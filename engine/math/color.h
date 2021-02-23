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

    Color blend(Color other) const;

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

    static Color red;
    static Color green;
    static Color blue;

private:
    glm::vec4 m_color_data;
};
