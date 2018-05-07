#ifndef SPHERE_H
#define SPHERE_H

#include "Hitable.h"
#include "Random.h"
#include "Vec3.h"

class Sphere : public Hitable {
public:
  Sphere() : Hitable() {}

  Sphere(const Vec3 &center, float radius, const std::shared_ptr<Material>& material) 
    : Hitable(material), Center(center), Radius(radius) {}

  virtual bool Hit(const Ray &ray, float tMin, float tMax,
                   HitResult &result) const override;

  Vec3 Center;
  float Radius;

private:
  inline bool EvaluateHit(const Ray &ray, float t, float tMin, float tMax,
                          HitResult &result) const;
};

bool Sphere::Hit(const Ray &ray, float tMin, float tMax,
                 HitResult &result) const {
  Vec3 oc = ray.Origin - Center;
  float a = Dot(ray.Direction, ray.Direction);
  float b = Dot(oc, ray.Direction);
  float c = Dot(oc, oc) - Radius * Radius;

  float discriminant = b * b - a * c;
  if (discriminant > 0) {
    float temp = (-b - std::sqrt(discriminant)) / a;
    if (EvaluateHit(ray, temp, tMin, tMax, result)) {
      return true;
    }
    temp = (-b + std::sqrt(discriminant)) / a;
    if (EvaluateHit(ray, temp, tMin, tMax, result)) {
      return true;
    }
  }

  return false;
}

inline bool Sphere::EvaluateHit(const Ray &ray, float t, float tMin, float tMax,
                                HitResult &result) const {
  if (t > tMin && t < tMax) {
    result.T = t;
    result.Point = ray.Evaluate(t);
    result.Normal = (result.Point - Center) / Radius;
    result.MaterialPtr = MaterialPtr;
    return true;
  }
  return false;
}

#endif
