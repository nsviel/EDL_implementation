#ifndef VK_CAMERA_H
#define VK_CAMERA_H

#include "../Struct/struct_mvp.h"
#include "../../../common.h"

class Engine;
class Camera;


class VK_camera
{
public:
  //Constructor / Destructor
  VK_camera(Engine* engineManager);
  ~VK_camera();

public:
  //Main functions
  void compute_mvp(Object* object);

private:
  Camera* cameraManager;
};

#endif
