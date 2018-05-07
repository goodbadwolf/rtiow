#include <fstream>
#include <iostream>
#include <limits>
#include <random>

#include "Camera.h"
#include "HitableList.h"
#include "Random.h"
#include "Ray.h"
#include "Sphere.h"
#include "Vec3.h"

Vec3 Color(const Ray &ray, Hitable *world) {
  HitResult result;
  if (world->Hit(ray, 0.001f, std::numeric_limits<float>::max(), result)) {
    Vec3 scatter = result.Point + result.Normal + RandomInUnitSphere();
    Ray scatteredRay(result.Point, scatter - result.Point);
    return 0.5f * Color(scatteredRay, world);
  } else {
    Vec3 direction = Normalized(ray.Direction);
    float t = 0.5f * (direction.Y() + 1.0f);
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
  if (argc > 2) {
    numSamples = std::stol(argv[2]);
  }

  Hitable *list[2];
  list[0] = new Sphere(Vec3(0.0f, 0.0f, -1.0f), 0.5f);
  list[1] = new Sphere(Vec3(0.0f, -100.5f, -1.0f), 100.0f);
  Hitable *world = new HitableList(list, 2);

  Camera camera;

  std::ofstream output("output.ppm", std::ios::out);
  output << "P3\n" << width << " " << height << "\n255\n";

  int noOfBounces = 0;
  for (int j = height - 1; j >= 0; --j) {
    for (int i = 0; i < width; ++i) {
      Vec3 color(0.0f, 0.0f, 0.0f);
      for (int s = 0; s < numSamples; ++s) {
        float u = (static_cast<float>(i) + Random::Next()) /
                  static_cast<float>(width);
        float v = (static_cast<float>(j) + Random::Next()) /
                  static_cast<float>(height);
        Ray ray = camera.GetRay(u, v);
        color += Color(ray, world);
      }

      color /= static_cast<float>(numSamples);
      color =
          Vec3(std::sqrt(color[0]), std::sqrt(color[1]), std::sqrt(color[2]));

      output << static_cast<int>(255.99f * color[0]) << " "
             << static_cast<int>(255.99f * color[1]) << " "
             << static_cast<int>(255.99f * color[2]) << "\n";
    }
  }

  delete list[0];
  delete list[1];
  delete world;
}
