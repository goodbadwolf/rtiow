#include <iostream>
#include <fstream>


#include "vec3.h"

int main()
{
  int width = 200;
  int height = 100;

  std::ofstream output("output.ppm", std::ios::out);
  output << "P3\n" << width << " " << height << "\n255\n";
  for(int j = height - 1; j >= 0; --j)
  {
    for(int i = 0; i < width; ++i)
    {
      vec3 color(static_cast<float>(i) / static_cast<float>(width), 
                 static_cast<float>(j) / static_cast<float>(height),
                 0.2f);
      output << static_cast<int>(255.99f * color[0]) << " " 
             << static_cast<int>(255.99f * color[1]) << " "
             << static_cast<int>(255.99f * color[2]) << "\n";
    }
  }
}
