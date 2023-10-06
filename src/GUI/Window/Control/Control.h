#ifndef CONTROL_H
#define CONTROL_H

#include <Specific/common.h>

class Engine;
class GUI;
class Data_node;
class Window;
class Camera;
class Scene;
class Transformation;


class Control
{
public:
  //Constructor / Destructor
  Control(GUI* gui);
  ~Control();

public:
  //Main function
  void exit();
  void reset();

  //Selected object function
  void selected_object_translation(vec3 translation);
  void selected_object_rotation(vec3 rotation);
  void selected_object_deletion();
  void selected_object_next();
  void object_deletion(Object* object);

private:
  Engine* engine;
  Scene* sceneManager;
  Window* window;
  Camera* cameraManager;
  Transformation* transformManager;
};

#endif
