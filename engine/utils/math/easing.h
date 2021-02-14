//
// Created by Michael on 14.02.2021.
//

#pragma once

namespace mathf::easingfunctions {

inline double Linear(double p) { return p; } // p^1 Note: In = Out = InOut
inline double InQuadratic(double p) { return p * p; } // p^2 = Math.pow(p,2)
inline double InCubic(double p) { return p * p * p; } // p^3 = Math.pow(p,3)
inline double InQuartic(double p) {
  return p * p * p * p;
} // p^4 = Math.pow(p,4)
inline double InQuintic(double p) {
  return p * p * p * p * p;
} // p^5 = Math.pow(p,5)
inline double InSextic(double p) {
  return p * p * p * p * p * p;
} // p^6 = Math.pow(p,6)
inline double InSeptic(double p) {
  return p * p * p * p * p * p * p;
} // p^7 = Math.pow(p,7)
inline double InOctic(double p) {
  return p * p * p * p * p * p * p * p;
} // p^8 = Math.pow(p,8)

inline double OutQuadratic(double p) {
  double m = p - 1;
  return 1 - m * m;
}
inline double OutCubic(double p) {
  double m = p - 1;
  return 1 + m * m * m;
}
inline double OutQuartic(double p) {
  double m = p - 1;
  return 1 - m * m * m * m;
}
inline double OutQuintic(double p) {
  double m = p - 1;
  return 1 + m * m * m * m * m;
}
inline double OutSextic(double p) {
  double m = p - 1;
  return 1 - m * m * m * m * m * m;
}
inline double OutSeptic(double p) {
  double m = p - 1;
  return 1 + m * m * m * m * m * m * m;
}
inline double OutOctic(double p) {
  double m = p - 1;
  return 1 - m * m * m * m * m * m * m * m;
}

inline double InOutQuadratic(double p) {
  double m = p - 1, t = p * 2;
  if (t < 1)
    return p * t;
  return 1 - m * m * 2;
}
inline double InOutCubic(double p) {
  double m = p - 1, t = p * 2;
  if (t < 1)
    return p * t * t;
  return 1 + m * m * m * 4;
}
inline double InOutQuartic(double p) {
  double m = p - 1, t = p * 2;
  if (t < 1)
    return p * t * t * t;
  return 1 - m * m * m * m * 8;
}
inline double InOutQuintic(double p) {
  double m = p - 1, t = p * 2;
  if (t < 1)
    return p * t * t * t * t;
  return 1 + m * m * m * m * m * 16;
}
inline double InOutSextic(double p) {
  double m = p - 1, t = p * 2;
  if (t < 1)
    return p * t * t * t * t * t;
  return 1 - m * m * m * m * m * m * 32;
}
inline double InOutSeptic(double p) {
  double m = p - 1, t = p * 2;
  if (t < 1)
    return p * t * t * t * t * t * t;
  return 1 + m * m * m * m * m * m * m * 64;
}
inline double InOutOctic(double p) {
  double m = p - 1, t = p * 2;
  if (t < 1)
    return p * t * t * t * t * t * t * t;
  return 1 - m * m * m * m * m * m * m * m * 128;
}

// Standard -- grouped by Type
inline double InBack(double p) {
  double k = 1.70158;
  return p * p * (p * (k + 1) - k);
}
inline double InOutBack(double p) {
  double m = p - 1, t = p * 2, k = 1.70158 * 1.525;
  if (p < 0.5)
    return p * t * (t * (k + 1) - k);
  else
    return 1 + 2 * m * m * (2 * m * (k + 1) + k);
} // NOTE: Can go negative! i.e. p = 0.008
inline double OutBack(double p) {
  double m = p - 1, k = 1.70158;
  return 1 + m * m * (m * (k + 1) + k);
}

inline double OutBounce(double p) {
  double r = 1 / 2.75;   // reciprocal
  double k1 = r;         // 36.36%
  double k2 = 2 * r;     // 72.72%
  double k3 = 1.5 * r;   // 54.54%
  double k4 = 2.5 * r;   // 90.90%
  double k5 = 2.25 * r;  // 81.81%
  double k6 = 2.625 * r; // 95.45%
  double k0 = 7.5625, t;

  /**/ if (p < k1) {
    return k0 * p * p;
  } else if (p < k2) {
    t = p - k3;
    return k0 * t * t + 0.75;
  } // 48/64
  else if (p < k4) {
    t = p - k5;
    return k0 * t * t + 0.9375;
  } // 60/64
  else {
    t = p - k6;
    return k0 * t * t + 0.984375;
  } // 63/64
}
inline double InBounce(double p) { return 1 - OutBounce(1 - p); }
inline double InOutBounce(double p) {
  double t = p * 2;
  if (t < 1)
    return 0.5 - 0.5 * OutBounce(1 - t);
  return 0.5 + 0.5 * OutBounce(t - 1);
}

inline double InCircle(double p) { return 1 - sqrt(1 - p * p); }
inline double InOutCircle(double p) {
  double m = p - 1, t = p * 2;
  if (t < 1)
    return (1 - sqrt(1 - t * t)) * 0.5;
  else
    return (sqrt(1 - 4 * m * m) + 1) * 0.5;
}
inline double OutCircle(double p) {
  double m = p - 1;
  return sqrt(1 - m * m);
}

inline double InElastic(double p) {
  double m = p - 1;
  return -pow(2, 10 * m) * sin((m * 40 - 3) * PI / 6);
}
inline double InOutElastic(double p) {
  double s = 2 * p - 1;              // remap: [0,0.5] -> [-1,0]
  double k = (80 * s - 9) * PI / 18; // and    [0.5,1] -> [0,+1]

  if (s < 0)
    return -0.5 * pow(2, 10 * s) * sin(k);
  else
    return 1 + 0.5 * pow(2, -10 * s) * sin(k);
}
inline double OutElastic(double p) {
  return 1 + (pow(2, 10 * -p) * sin((-p * 40 - 3) * PI / 6));
}

// NOTE: 'Exponent2' needs clamping for 0 and 1 respectively
inline double InExponent2(double p) {
  if (p <= 0)
    return 0;
  return pow(2, 10 * (p - 1));
}
inline double InOutExponent2(double p) {
  if (p <= 0)
    return 0;
  if (p >= 1)
    return 1;
  if (p < 0.5)
    return pow(2, 10 * (2 * p - 1) - 1);
  else
    return 1 - pow(2, -10 * (2 * p - 1) - 1);
}
inline double OutExponent2(double p) {
  if (p >= 1)
    return 1;
  return 1 - pow(2, -10 * p);
}

inline double InSine(double p) { return 1 - cos(p * PI * 0.5); }
inline double InOutSine(double p) { return 0.5 * (1 - cos(p * PI)); }
inline double OutSine(double p) { return sin(p * PI * 0.5); }

// Non-Standard
inline double InExponentE(double p) {
  if (p <= 0)
    return 0;
  return pow(M_E, -10 * (1 - p));
} // Scale 0..1 -> p^-10 .. p^0
inline double OutExponentE(double p) { return 1 - InExponentE(1 - p); }
inline double InOutExponentE(double p) {
  double t = p * 2;
  if (t < 1)
    return 0.5 - 0.5 * OutExponentE(1 - t);
  return 0.5 + 0.5 * OutExponentE(t - 1);
}
inline double OutLog10(double p) {
  return log10((p * 9) + 1);
} // Scale 0..1 -> Log10( 1 ) .. Log10( 10 )

inline double InLog10(double p) { return 1 - OutLog10(1 - p); }
inline double InOutLog10(double p) {
  double t = p * 2;
  if (t < 1)
    return 0.5 - 0.5 * OutLog10(1 - t);
  return 0.5 + 0.5 * OutLog10(t - 1);
}
inline double OutSquareRoot(double p) { return sqrt(p); }

inline double InSquareRoot(double p) { return 1 - OutSquareRoot(1 - p); }
inline double InOutSquareRoot(double p) {
  double t = p * 2;
  if (t < 1)
    return 0.5 - 0.5 * OutSquareRoot(1 - t);
  return 0.5 + 0.5 * OutSquareRoot(t - 1);
}

inline double Smoothstep(double t, double x0, double x1) {

  double p = (t - x0) / (x1 - x0);
  if (p < 0)
    p = 0;
  if (p > 1)
    p = 1;

  return p * p * (3 - 2 * p);
}
} // namespace mathf::easingfunctions