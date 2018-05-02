#include <iostream>
#include <fstream>


#include "ray.h"
#include "vec3.h"

bool hit_sphere(const vec3& center, float radius, const ray& r)
{
  vec3 oc = r.origin() - center;
  float a = dot(r.direction(), r.direction());
  float b = 2.0f * dot(oc, r.direction());
  float c = dot(oc, oc) - radius * radius;
  float discriminant = (b * b) - (4.0f * a * c);
  return (discriminant > 0);
}

vec3 color(const ray& r) 
{
  if(hit_sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f, r))
  {
    return vec3(1.0f, 0.0f, 0.0f);
  }
  vec3 unit_direction = unit_vector(r.direction());
  float t = 0.5f * (unit_direction.y() + 1.0f);
  return (1.0f - t) * vec3 (1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}

int main()
{
  int width = 200;
  int height = 100;

  std::ofstream output("output.ppm", std::ios::out);
  output << "P3\n" << width << " " << height << "\n255\n";
  vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
  vec3 horizontal(4.0f, 0.0f, 0.0f);
  vec3 vertical(0.0f, 2.0f, 0.0f);
  vec3 origin(0.0f, 0.0f, 0.0f);
  for(int j = height - 1; j >= 0; --j)
  {
    for(int i = 0; i < width; ++i)
    {
      float u = static_cast<float>(i) / static_cast<float>(width);
      float v = static_cast<float>(j) / static_cast<float>(height);
      ray r(origin, lower_left_corner + u * horizontal + v * vertical);
      vec3 c = color(r);
      output << static_cast<int>(255.99f * c[0]) << " " 
             << static_cast<int>(255.99f * c[1]) << " "
             << static_cast<int>(255.99f * c[2]) << "\n";
    }
  }
}
