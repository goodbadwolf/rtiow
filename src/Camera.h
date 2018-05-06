#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"

class Camera {
public:
  Camera() 
    : Origin(0.0f, 0.0f, 0.0f)
    , Horizontal(4.0f, 0.0f, 0.0f)
    , Vertical(0.0f, 2.0f, 0.0f)
    , LowerLeft(-2.0f, -1.0f, -1.0f)
  {}

  Ray GetRay(float u, float v) 
  {
    return Ray(Origin, (LowerLeft + u * Horizontal + v * Vertical) - Origin);
  }

  Vec3 Origin;
  Vec3 Horizontal;
  Vec3 Vertical;
  Vec3 LowerLeft;
};

#endif
