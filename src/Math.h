#ifndef UTILS_H
#define UTILS_H

#include <algorithm>

inline float Clamp(float f, float min, float max) {
  return std::min(std::max(f, min), max);
}

inline float Clamp01(float f) {
  return Clamp(f, 0.0f, 1.0f);
}

#endif
