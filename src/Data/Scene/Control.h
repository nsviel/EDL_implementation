#ifndef CONTROL_H
#define CONTROL_H

#include "../../common.h"

class Node;
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
  void selected_object_rotation(vec3 rotation);
  void selected_object_deletion();

private:
  Node* node;
  Scene* sceneManager;
  Dimension* dimManager;
  Camera* cameraManager;
};

#endif
