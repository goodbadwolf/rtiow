#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

struct Ray {
  Ray() {}

  Ray(const Vec3 &origin, const Vec3 &direction)
      : Origin(origin), Direction(direction) {
    Origin = origin;
    Direction = direction;
  }

  Vec3 Evaluate(float t) const { return Origin + t * Direction; }

  Vec3 Origin;
  Vec3 Direction;
};

#endif
