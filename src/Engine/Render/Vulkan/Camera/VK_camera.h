#ifndef VK_CAMERA_H
#define VK_CAMERA_H

#include "../Struct/struct_binding.h"
#include <Specific/common.h>

class VK_engine;
class Camera;


class VK_camera
{
public:
  //Constructor / Destructor
  VK_camera(VK_engine* vk_engine);
  ~VK_camera();

public:
  //Main functions
  void compute_mvp(Object* object);

private:
  Camera* cameraManager;
};

#endif
