#ifndef VK_CAMERA_H
#define VK_CAMERA_H

#include "../VK_struct.h"
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
  MVP get_mvp();

private:
  Camera* cameraManager;
};

#endif
