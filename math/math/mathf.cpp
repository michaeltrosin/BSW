//
// Created by Michael on 23.02.2021.
//

#include "mathf.h"

long double mathf::operator""_to_deg(long double value) { return value * RAD_2_DEG; }
long double mathf::operator""_to_rad(long double value) { return value * DEG_2_RAD; }

double mathf::normalize(double value, double min, double max) { return (value - min) / (max - min); }

double mathf::denormalize(double normalized, double min, double max) { return normalized * (max - min) + min; }

double mathf::map(double value, double old_min, double old_max, double new_min, double new_max) {
    return denormalize(normalize(value, old_min, old_max), new_min, new_max);
}

double mathf::clamp(double value, double min, double max) { return value < min ? min : value > max ? max : value; }

double mathf::max(double value_1, double value_2) { return value_1 > value_2 ? value_1 : value_2; }

double mathf::min(double value_1, double value_2) { return value_1 < value_2 ? value_1 : value_2; }

bool mathf::is_between(double value, double min, double max) { return min <= value && value <= max; }

double mathf::sign(double f) { return f >= 0.0 ? 1.0 : -1.0; }

double mathf::abs(double f) { return f < 0 ? -f : f; }

double mathf::clamp_01(double value) { return clamp(value, 0.0, 1.0); }

double mathf::lerp(double a, double b, double t) { return a + (b - a) * clamp_01(t); }

double mathf::lerp_unclamped(double a, double b, double t) { return a + (b - a) * t; }

double mathf::repeat(double t, double length) { return clamp(t - floor(t / length) * length, 0.0f, length); }

double mathf::lerp_angle(double a, double b, double t) {
    double delta = repeat((b - a), 360);
    if (delta > 180) delta -= 360;
    return a + delta * clamp_01(t);
}

double mathf::smooth_step(double from, double to, double t) {
    t = clamp_01(t);
    t = -2.0 * t * t * t + 3.0 * t * t;
    return to * t + from * (1.0 - t);
}

double mathf::move_towards(double current, double target, double max_delta) {
    if (abs(target - current) <= max_delta) return target;
    return current + sign(target - current) * max_delta;
}

double mathf::delta_angle(double current, double target) {
    double delta = repeat((target - current), 360.0);
    if (delta > 180.0) delta -= 360.0;
    return delta;
}

double mathf::move_towards_angle(double current, double target, double max_delta) {
    double d_a = delta_angle(current, target);
    if (-max_delta < d_a && d_a < max_delta) return target;
    target = current + d_a;
    return move_towards(current, target, max_delta);
}

double mathf::inverse_lerp(double a, double b, double value) {
    if (a != b) return clamp_01((value - a) / (b - a));
    else
        return 0.0;
}