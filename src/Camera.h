#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"

class Camera {
public:
  Camera(const Vec3& origin, const Vec3& lookAt, const Vec3& vup, float fov, float aspectRatio)
      : Origin(origin) {
    float theta = fov * M_PI / 180.0f;
    float halfHeight = std::tan(theta / 2.0f);
    float halfWidth = aspectRatio * halfHeight;
    
    Vec3 w = Normalized(Origin - lookAt);
    Vec3 u = Normalized(Cross(vup, w));
    Vec3 v = Cross(w, u);

    Horizontal = 2.0f * halfWidth * u;
    Vertical = 2.0f * halfHeight * v;
    LowerLeft = Origin - halfWidth * u - halfHeight * v - w;
  }

  Ray GetRay(float u, float v) {
    return Ray(Origin, (LowerLeft + u * Horizontal + v * Vertical) - Origin);
  }

  Vec3 Origin;
  Vec3 Horizontal;
  Vec3 Vertical;
  Vec3 LowerLeft;
};

#endif
