#include <fstream>
#include <iostream>
#include <limits>
#include <random>

#include "Camera.h"
#include "HitableList.h"
#include "Material.h"
#include "Random.h"
#include "Ray.h"
#include "Sphere.h"
#include "Vec3.h"

const int MAX_DEPTH = 50;

Vec3 Color(const Ray &ray, Hitable *world, int depth) {
  HitResult result;
  if (world->Hit(ray, 0.001f, std::numeric_limits<float>::max(), result)) {
    Vec3 attenuation;
    Ray scattered;
    if(depth < MAX_DEPTH && 
       result.MaterialPtr->Scatter(ray, result, attenuation, scattered)) {
      return attenuation * Color(scattered, world, depth + 1);
    } else {
      return Vec3(0.0f, 0.0f, 0.0f);
    }
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

  std::shared_ptr<Material> materials[4];
  materials[0] = std::make_shared<Lambertian>(Vec3(0.8f, 0.3f, 0.3f));
  materials[1] = std::make_shared<Lambertian>(Vec3(0.8f, 0.8f, 0.0f));
  materials[2] = std::make_shared<Metal>(Vec3(0.8f, 0.6f, 0.2f), 1.0f);
  materials[3] = std::make_shared<Metal>(Vec3(0.8f, 0.8f, 0.8f), 0.3f);

  Hitable* list[4];
  list[0] = new Sphere(Vec3(0.0f, 0.0f, -1.0f),    0.5f,   materials[0]);
  list[1] = new Sphere(Vec3(0.0f, -100.5f, -1.0f), 100.0f, materials[1]);
  list[2] = new Sphere(Vec3(1.0f, 0.0f, -1.0f),    0.5f,   materials[2]);
  list[3] = new Sphere(Vec3(-1.0f, 0.0f, -1.0f),   0.5f,   materials[3]);
  Hitable *world = new HitableList(list, 4);
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
        color += Color(ray, world, 0);
      }

      color /= static_cast<float>(numSamples);
      color =
          Vec3(std::sqrt(color[0]), std::sqrt(color[1]), std::sqrt(color[2]));

      output << static_cast<int>(255.99f * color[0]) << " "
             << static_cast<int>(255.99f * color[1]) << " "
             << static_cast<int>(255.99f * color[2]) << "\n";
    }
  }

  for(int i = 0; i < 4; ++i) {
    delete list[i];
  }

  delete world;
}
