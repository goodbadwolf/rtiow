#include <iostream>
#include <fstream>

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
      float r = static_cast<float>(i) / static_cast<float>(width);
      float g = static_cast<float>(j) / static_cast<float>(height);
      float b = 0.2f;
      output << static_cast<int>(255.99f * r) << " " 
             << static_cast<int>(255.99f * g) << " "
             << static_cast<int>(255.99f * b) << "\n";
    }
  }
}
