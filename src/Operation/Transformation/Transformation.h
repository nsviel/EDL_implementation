#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "../../common.h"


class Transformation
{
public:
  // Constructor / Destructor
  Transformation();
  ~Transformation();

public:
  // Translation
  void make_translation(Object* object, vec3 trans);
  void make_translation(vector<vec3>& XYZ, vec3 trans);

  // Rotation
  void make_rotation(Object* object, vec3 COM, vec3 angles);

private:
};

#endif
