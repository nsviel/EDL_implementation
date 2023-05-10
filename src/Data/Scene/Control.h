#ifndef CONTROL_H
#define CONTROL_H

#include "../../common.h"

class Node_data;
class Dimension;
class Camera;
class Scene;


class Control
{
public:
  //Constructor / Destructor
  Control(Node_data* node_data);
  ~Control();

public:
  //Main function
  void exit();
  void reset();
  void selected_object_translation(vec3 translation);

private:
  Scene* sceneManager;
  Dimension* dimManager;
  Camera* cameraManager;
};

#endif
