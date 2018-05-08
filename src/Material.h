#ifndef MATERIAL_H
#define MATERIAL_H

#include "Hitable.h"
#include "Math.h"
#include "Ray.h"
#include "Vec3.h"

class Material {
public:
  virtual bool Scatter(const Ray &ray, const HitResult &hit, Vec3 &attenuation,
                       Ray &scattered) const = 0;
};

class Lambertian : public Material {
public:
  Lambertian(const Vec3 &albedo) : Albedo(albedo) {}

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
  Metal(const Vec3 &albedo, float fuzz) : Albedo(albedo), Fuzz(Clamp01(fuzz)) {}

  virtual bool Scatter(const Ray &ray, const HitResult &hit, Vec3 &attenuation,
                       Ray &scattered) const override {
    Vec3 reflected = Reflect(Normalized(ray.Direction), hit.Normal);
    scattered = Ray(hit.Point, reflected + Fuzz * RandomInUnitSphere());
    attenuation = Albedo;
    return (Dot(scattered.Direction, hit.Normal) > 0);
  }

  Vec3 Albedo;
  float Fuzz;
};

float Schlick(float cosine, float refIdx) {
  float r0 = (1.0f - refIdx) / (1.0f + refIdx);
  r0 = r0 * r0;
  return r0 + (1.0f - r0) * std::pow((1.0f - cosine), 5.0f);
}

class Dielectric : public Material {
public:
  Dielectric(float refIdx) : RefIdx(refIdx) {}

  virtual bool Scatter(const Ray &ray, const HitResult &hit, Vec3 &attenuation,
                       Ray &scattered) const override {
    Vec3 outwardNormal;
    Vec3 reflected = Reflect(ray.Direction, hit.Normal);
    float niOverNt;
    attenuation = Vec3(1.0f, 1.0f, 1.0f);
    Vec3 refracted;
    float reflectionProbability;
    float cosine;
    if (Dot(ray.Direction, hit.Normal) > 0) {
      outwardNormal = -hit.Normal;
      niOverNt = RefIdx;
      cosine = RefIdx * Dot(ray.Direction, hit.Normal) / ray.Direction.Length();
    } else {
      outwardNormal = hit.Normal;
      niOverNt = 1.0f / RefIdx;
      cosine = -Dot(ray.Direction, hit.Normal) / ray.Direction.Length();
    }
    if (Refract(ray.Direction, outwardNormal, niOverNt, refracted)) {
      reflectionProbability = Schlick(cosine, RefIdx);
    } else {
      scattered = Ray(hit.Point, reflected);
      reflectionProbability = 1.0f;
    }
    if (Random::Next() < reflectionProbability) {
      scattered = Ray(hit.Point, reflected);
    } else {
      scattered = Ray(hit.Point, refracted);
    }
    return true;
  }

  float RefIdx;
};

#endif
