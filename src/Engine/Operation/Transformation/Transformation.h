#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <Specific/Struct/struct_object.h>
#include <glm/glm.hpp>
#include <vector>

using namespace std;
using namespace glm;


class Transformation
{
public:
  // Constructor / Destructor
  Transformation();
  ~Transformation();

public:
  // Translation
  void make_translation(Object* object, vec3 trans);

  // Rotation
  void make_rotation(Object* object, vec3 COM, vec3 angles);

  //Scaling
  void make_scaling(Object* object, float scale);

  //Subfunction
  mat4 get_translation_mat(vec3 trans);
  mat4 get_translation_mat_neye(vec3 trans);
  mat4 get_rotation_mat(vec3 radian);

private:
};

#endif
