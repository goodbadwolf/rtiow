#ifndef HITABLE_H
#define HITABLE_H

#include "Ray.h"

struct HitResult {
  float T;
  Vec3 Point;
  Vec3 Normal;
};

class Hitable {
public:

  virtual bool Hit(const Ray &ray, float tMin, float tMax, HitResult& result) const = 0;
};

#endif // HITABLE_H