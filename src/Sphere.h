#ifndef SPHERE_H
#define SPHERE_H

#include "Hitable.h"
#include "Random.h"
#include "Vec3.h"

class Sphere : public Hitable {
public:
  Sphere() {}

  Sphere(const Vec3& center, float radius)
    : Center(center)
    , Radius(radius)
  {};

  virtual bool Hit(const Ray &ray, float tMin, float tMax, HitResult& result) const override;

  Vec3 Center;
  float Radius;

private:
  inline bool EvaluateHit(const Ray& ray, float t, float tMin, float tMax, HitResult& result) const;
};


bool Sphere::Hit(const Ray &ray, float tMin, float tMax, HitResult& result) const
{
  Vec3 oc = ray.Origin - Center;
  float a =  Dot(ray.Direction, ray.Direction);
  float b = Dot(oc, ray.Direction);
  float c = Dot(oc, oc) - Radius * Radius;

  float discriminant = b * b - a * c;
  if(discriminant > 0) {
    float temp = (-b - std::sqrt(discriminant)) / a;
    if(EvaluateHit(ray, temp, tMin, tMax, result)) {
      return true;
    }
    temp = (-b + std::sqrt(discriminant)) / a;
    if(EvaluateHit(ray, temp, tMin, tMax, result)) {
      return true;
    }
  }

  return false;
}

inline bool Sphere::EvaluateHit(const Ray& ray, float t, float tMin, float tMax, HitResult& result) const
{
  if(t > tMin && t < tMax) {
    result.T = t;
    result.Point = ray.Evaluate(t);
    result.Normal = (result.Point - Center) / Radius;
    return true;
  }
  return false;
}

Vec3 RandomInUnitSphere() {
  Vec3 point;
  do {
    point = 2.0f * Vec3(Random::Next(), Random::Next(), Random::Next()) - 
            Vec3(1.0f, 1.0f, 1.0f);
  } while(point.LengthSquared() >= 1.0f);
  return point;
}

#endif
