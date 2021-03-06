#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

#include "Random.h"

struct Vec3 {
public:
  Vec3() {}

  Vec3(float e0, float e1, float e2) {
    e[0] = e0;
    e[1] = e1;
    e[2] = e2;
  }

  inline float X() const { return e[0]; }
  inline float Y() const { return e[1]; }
  inline float Z() const { return e[2]; }
  inline float R() const { return e[0]; }
  inline float G() const { return e[1]; }
  inline float B() const { return e[2]; }

  inline const Vec3 &operator+() const { return *this; }
  inline Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
  inline float operator[](int i) const { return e[i]; }
  inline float &operator[](int i) { return e[i]; };

  inline Vec3 &operator+=(const Vec3 &v2);
  inline Vec3 &operator-=(const Vec3 &v2);
  inline Vec3 &operator*=(const Vec3 &v2);
  inline Vec3 &operator/=(const Vec3 &v2);
  inline Vec3 &operator*=(const float t);
  inline Vec3 &operator/=(const float t);

  inline float Length() const {
    return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
  }

  inline float LengthSquared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }

  void Print(const char *name = nullptr, bool endLine = false) {
    if (name) {
      std::cout << name << ": ";
    }

    std::cout << "(" << e[0] << ", " << e[1] << ", " << e[2] << ")";

    if (endLine) {
      std::cout << std::endl;
    }
  }

  inline void Normalize();

  float e[3];
};

inline std::istream &operator>>(std::istream &is, Vec3 &t) {
  is >> t.e[0] >> t.e[1] >> t.e[2];
  return is;
}

inline std::ostream &operator<<(std::ostream &os, const Vec3 &t) {
  os << t.e[0] << " " << t.e[1] << " " << t.e[2];
  return os;
}

inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2) {
  return Vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2) {
  return Vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2) {
  return Vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline Vec3 operator/(const Vec3 &v1, const Vec3 &v2) {
  return Vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline Vec3 operator*(float t, const Vec3 &v) {
  return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vec3 operator/(Vec3 v, float t) {
  return Vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline Vec3 operator*(const Vec3 &v, float t) {
  return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline float Dot(const Vec3 &v1, const Vec3 &v2) {
  return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

inline Vec3 Cross(const Vec3 &v1, const Vec3 &v2) {
  return Vec3((v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
              (-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0])),
              (v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
}

inline Vec3 &Vec3::operator+=(const Vec3 &v) {
  e[0] += v.e[0];
  e[1] += v.e[1];
  e[2] += v.e[2];
  return *this;
}

inline Vec3 &Vec3::operator*=(const Vec3 &v) {
  e[0] *= v.e[0];
  e[1] *= v.e[1];
  e[2] *= v.e[2];
  return *this;
}

inline Vec3 &Vec3::operator/=(const Vec3 &v) {
  e[0] /= v.e[0];
  e[1] /= v.e[1];
  e[2] /= v.e[2];
  return *this;
}

inline Vec3 &Vec3::operator-=(const Vec3 &v) {
  e[0] -= v.e[0];
  e[1] -= v.e[1];
  e[2] -= v.e[2];
  return *this;
}

inline Vec3 &Vec3::operator*=(const float t) {
  e[0] *= t;
  e[1] *= t;
  e[2] *= t;
  return *this;
}

inline Vec3 &Vec3::operator/=(const float t) {
  float k = 1.0 / t;

  e[0] *= k;
  e[1] *= k;
  e[2] *= k;
  return *this;
}

inline Vec3 Normalized(const Vec3 &v) { return v / v.Length(); }

inline void Vec3::Normalize() {
  float k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
  e[0] *= k;
  e[1] *= k;
  e[2] *= k;
}

inline Vec3 Reflect(const Vec3 &vec, const Vec3 &normal) {
  return vec - 2 * Dot(vec, normal) * normal;
}

inline bool Refract(const Vec3 &vec, const Vec3 &normal, float niOverNt,
                    Vec3 &refracted) {
  Vec3 uv = Normalized(vec);
  float dt = Dot(uv, normal);
  float discriminant = 1.0f - niOverNt * niOverNt * (1.0f - dt * dt);
  if (discriminant > 0) {
    refracted =
        niOverNt * (uv - normal * dt) - normal * std::sqrt(discriminant);
    return true;
  } else {
    return false;
  }
}

Vec3 RandomInUnitSphere() {
  Vec3 point;
  do {
    point = 2.0f * Vec3(Random::Next(), Random::Next(), Random::Next()) -
            Vec3(1.0f, 1.0f, 1.0f);
  } while (point.LengthSquared() >= 1.0f);
  return point;
}

#endif
