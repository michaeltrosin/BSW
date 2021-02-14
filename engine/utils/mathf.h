//
// Created by Michael on 26.01.2021.
//
#pragma once

#include <cmath>

namespace mathf {

inline double Normalize(double value, double min, double max) {
  return (value - min) / (max - min);
}

inline double Denormalize(double normalized, double min, double max) {
  return normalized * (max - min) + min;
}

inline double Map(double value, double old_min, double old_max, double new_min,
                  double new_max) {
  return Denormalize(Normalize(value, old_min, old_max), new_min, new_max);
}

inline double Clamp(double value, double min, double max) {
  return value < min ? min : value > max ? max : value;
}

inline double Sign(double f) { return f >= 0.0 ? 1.0 : -1.0; }
inline double Abs(double f) { return f < 0 ? -f : f; }

inline constexpr double PI = M_PI;

/**
 * Degrees-to-radians conversion constant (RO).
 */
inline constexpr double DEG2RAD = PI * 2.0 / 360.0;

/**
 * Radians-to-degrees conversion constant (RO).
 */
inline constexpr double RAD2DEG = 1.0 / DEG2RAD;

/**
 * Clamps value between 0 and 1 and returns value
 */
inline double Clamp01(double value) { return Clamp(value, 0.0, 1.0); }

/**
 * Interpolates between /a/ and /b/ by /t/. /t/ is clamped between 0 and 1.
 */
inline double Lerp(double a, double b, double t) {
  return a + (b - a) * Clamp01(t);
}

/**
 * Interpolates between /a/ and /b/ by /t/ without clamping the interpolant.
 * */
inline double LerpUnclamped(double a, double b, double t) {
  return a + (b - a) * t;
}
/**
 * Loops the value t, so that it is never larger than length and never smaller
 * than 0.
 */
inline double Repeat(double t, double length) {
  return Clamp(t - floor(t / length) * length, 0.0f, length);
}

/**
 * Same as Lerp but makes sure the values interpolate correctly when they
 * wrap around 360 degrees.
 */
inline double LerpAngle(double a, double b, double t) {
  double delta = Repeat((b - a), 360);
  if (delta > 180)
    delta -= 360;
  return a + delta * Clamp01(t);
}

/**
 * Interpolates between /min/ and /max/ with smoothing at the limits.
 */
inline double SmoothStep(double from, double to, double t) {
  t = Clamp01(t);
  t = -2.0 * t * t * t + 3.0 * t * t;
  return to * t + from * (1.0 - t);
}

/**
 * Moves a value /current/ towards /target/.
 */
inline double MoveTowards(double current, double target, double max_delta) {
  if (Abs(target - current) <= max_delta)
    return target;
  return current + Sign(target - current) * max_delta;
}

/**
 * Calculates the shortest difference between two given angles.
 */
inline double DeltaAngle(double current, double target) {
  double delta = Repeat((target - current), 360.0F);
  if (delta > 180.0F)
    delta -= 360.0F;
  return delta;
}

/**
 * Same as ::ref::MoveTowards but makes sure the values interpolate correctly
 * when they wrap around 360 degrees.
 */
inline double MoveTowardsAngle(double current, double target,
                               double max_delta) {
  double delta_angle = DeltaAngle(current, target);
  if (-max_delta < delta_angle && delta_angle < max_delta)
    return target;
  target = current + delta_angle;
  return MoveTowards(current, target, max_delta);
}

/**
 * Calculates the ::ref::Lerp parameter between of two values.
 */
inline double InverseLerp(double a, double b, double value) {
  if (a != b)
    return Clamp01((value - a) / (b - a));
  else
    return 0.0f;
}
} // namespace mathf