#ifndef HITABLE_H
#define HITABLE_H

#include "Ray.h"

#include <memory>

class Material;

struct HitResult {
  float T;
  Vec3 Point;
  Vec3 Normal;
  std::shared_ptr<Material> MaterialPtr;
};

class Hitable {
public:
  Hitable () : MaterialPtr(nullptr) {}

  Hitable (const std::shared_ptr<Material>& material)
    : MaterialPtr(material) {}

  virtual bool Hit(const Ray &ray, float tMin, float tMax,
                   HitResult &result) const = 0;

  std::shared_ptr<Material> MaterialPtr;
};

#endif // HITABLE_H
