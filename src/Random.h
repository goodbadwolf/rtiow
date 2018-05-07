#ifndef RANDOM_H
#define RANDOM_H

class Random {
public:
  Random() : Generator(Device()), Distribution(0.0f, 1.0f) {}

  float GetNext() { return Distribution(Generator); }

  static float Next() {
    static Random random;
    return random.GetNext();
  }

private:
  std::random_device Device;
  std::mt19937 Generator;
  std::uniform_real_distribution<float> Distribution;
};

#endif
