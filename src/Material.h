#ifndef MATERIAL_H
#define MATERIAL_H

#include "Hitable.h"
#include "Ray.h"
#include "Vec3.h"

class Material {
public:
  virtual bool Scatter(const Ray &ray, const HitResult &hit, Vec3 &attenuation,
                       Ray &scattered) const = 0;
};

class Lambertian : public Material {
public:
  Lambertian(const Vec3& albedo) 
    : Albedo(albedo) {}

  virtual bool Scatter(const Ray &ray, const HitResult &hit, Vec3 &attenuation,
                       Ray &scattered) const override {
    Vec3 target = hit.Point + hit.Normal + RandomInUnitSphere();
    scattered = Ray(hit.Point, target - hit.Point);
    attenuation = Albedo;
    return true;
  }

  Vec3 Albedo;
};

class Metal : public Material {
public:
  Metal(const Vec3& albedo)
    : Albedo(albedo) {}

  virtual bool Scatter(const Ray& ray, const HitResult& hit, Vec3& attenuation, 
                       Ray& scattered) const override {
    Vec3 reflected = Reflect(Normalized(ray.Direction), hit.Normal);
    scattered = Ray(hit.Point, reflected);
    attenuation = Albedo;
    return (Dot(reflected, hit.Normal) > 0);
  }

  Vec3 Albedo;
};

#endif
