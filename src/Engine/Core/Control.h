#ifndef CONTROL_H
#define CONTROL_H

#include "../../common.h"

class Node_engine;
class Dimension;
class Camera;


class Control
{
public:
  //Constructor / Destructor
  Control(Node_engine* node_engine);
  ~Control();

public:
  //Main function
  void exit();
  void reset();

private:
  Node_engine* node_engine;
  Dimension* dimManager;
  Camera* cameraManager;
};

#endif
