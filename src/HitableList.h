#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H

#include "Hitable.h"

class HitableList : public Hitable {
public:
  HitableList() {}

  HitableList(Hitable** list, int size)
    : List(list)
    , Size(size)
  {}

  virtual bool Hit(const Ray& ray, float tMin, float tMax, HitResult& result) const;

  Hitable** List;
  int Size;
};

bool HitableList::Hit(const Ray& ray, float tMin, float tMax, HitResult& result) const
{
  HitResult tempResult;
  bool hit = false;
  float closest = tMax;
  for(int i = 0; i < Size; ++i) {
    if(List[i]->Hit(ray, tMin, closest, tempResult)) {
      hit = true;
      closest = tempResult.T;
      result = tempResult;
    }
  }
  return hit;
}

#endif
