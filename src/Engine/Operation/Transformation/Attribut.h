#ifndef ATTRIBUT_H
#define ATTRIBUT_H

#include <Specific/Struct/struct_object.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace glm;


class Attribut
{
public:
  // Constructor / Destructor
  Attribut();
  ~Attribut();

public:
  //Main functions
  void compute_MinMax(Object* object);

private:
};

#endif
