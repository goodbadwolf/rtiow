#ifndef MATERIAL_H
#define MATERIAL_H

#include "Hitable.h"
#include "Ray.h"

class Material {
public:
  virtual bool Scatter(const Ray& ray, const HitResult& hit, Vec3& attenuation, 
                       Ray& scattered) = 0;
};
#endif
