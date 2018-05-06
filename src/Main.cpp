#include <fstream>
#include <iostream>
#include <limits>
#include <random>

#include "Camera.h"
#include "HitableList.h"
#include "Ray.h"
#include "Sphere.h"
#include "Vec3.h"

Vec3 Color(const Ray& ray, Hitable* world) {
  HitResult hitResult;
  if(world->Hit(ray, 0.0f, std::numeric_limits<float>::max(), hitResult))
  {
    Vec3 normal = hitResult.Normal;
    return 0.5f * Vec3(normal.X() + 1.0f,
                       normal.Y() + 1.0f, 
                       normal.Z() + 1.0f);
  }
  else {
    Vec3 normal = Normalized(ray.Direction);
    float t = 0.5f * (normal.Y() + 1.0f);
    return (1.0f - t) * Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
  }
}

int main(int argc, char *argv[]) {
  int width = 200;
  int height = 100;
  int numSamples = 100;
  if (argc > 1) {
    height = std::stol(argv[1]);
    width = 2 * height;
  }
  if(argc > 2) {
    numSamples = std::stol(argv[2]);
  }

  Hitable* list[2];
  list[0] = new Sphere(Vec3(0.0f, 0.0f, -1.0f), 0.5f);
  list[1] = new Sphere(Vec3(0.0f, -100.5f, -1.0f), 100.0f);
  Hitable* world = new HitableList(list, 2);

  Camera camera;

  std::ofstream output("output.ppm", std::ios::out);
  output << "P3\n" << width << " " << height << "\n255\n";

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dist(0.0f, 1.0f);

  for (int j = height - 1; j >= 0; --j) {
    for (int i = 0; i < width; ++i) {
      Vec3 color(0.0f, 0.0f, 0.0f);
      for(int s = 0;  s < numSamples; ++s) {
        float u = (static_cast<float>(i) + dist(gen)) / static_cast<float>(width);
        float v = (static_cast<float>(j) + dist(gen)) / static_cast<float>(height);
        Ray ray = camera.GetRay(u, v);
        color += Color(ray, world);
      }

      color /= static_cast<float>(numSamples);

      output << static_cast<int>(255.99f * color[0]) << " "
             << static_cast<int>(255.99f * color[1]) << " "
             << static_cast<int>(255.99f * color[2]) << "\n";
    }
  }

  delete list[0];
  delete list[1];
  delete world;
}
