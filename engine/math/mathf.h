//
// Created by Michael on 26.01.2021.
//
#pragma once

#include <cmath>
#include <functional>

namespace mathf {
#define PI = (double) M_PI

/**
 * Degrees-to-radians conversion constant (RO).
 */
#define DEG_2_RAD = (PI * 2.0 / 360.0)

/**
 * Radians-to-degrees conversion constant (RO).
 */
#define RAD_2_DEG = (1.0 / DEG_2_RAD)

double normalize(double value, double min, double max);
double denormalize(double normalized, double min, double max);
double map(double value, double old_min, double old_max, double new_min, double new_max);
double clamp(double value, double min, double max);
double max(double value_1, double value_2);
double min(double value_1, double value_2);
bool is_between(double value, double min, double max);
double sign(double f);
double abs(double f);

/**
 * Clamps value between 0 and 1 and returns value
 */
double clamp_01(double value);

/**
 * Interpolates between /a/ and /b/ by /t/. /t/ is clamped between 0 and 1.
 */
double lerp(double a, double b, double t);

/**
 * Interpolates between /a/ and /b/ by /t/ without clamping the interpolant.
 * */
double lerp_unclamped(double a, double b, double t);
/**
 * Loops the value t, so that it is never larger than length and never smaller
 * than 0.
 */
double repeat(double t, double length);

/**
 * Same as lerp but makes sure the values interpolate correctly when they
 * wrap around 360 degrees.
 */
double lerp_angle(double a, double b, double t);

/**
 * Interpolates between /min/ and /max/ with smoothing at the limits.
 */
double smooth_step(double from, double to, double t);

/**
 * Moves a value /current/ towards /target/.
 */
double move_towards(double current, double target, double max_delta);

/**
 * Calculates the shortest difference between two given angles.
 */
double delta_angle(double current, double target);

/**
 * Same as ::ref::move_towards but makes sure the values interpolate correctly
 * when they wrap around 360 degrees.
 */
double move_towards_angle(double current, double target, double max_delta);

/**
 * Calculates the ::ref::lerp parameter between of two values.
 */
double inverse_lerp(double a, double b, double value);
}// namespace mathf