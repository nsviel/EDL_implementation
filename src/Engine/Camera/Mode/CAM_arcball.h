#ifndef CAM_ARCBALL_H
#define CAM_ARCBALL_H

#include "../struct_cam.h"
#include "../../../common.h"

class Node_engine;
class Dimension;


class CAM_arcball
{
public:
  CAM_arcball(Node_engine* node_engine);
  ~CAM_arcball();

public:
  mat4 arcball_view_mat(Cam* camera);
  void arcball_cam_mouse(Cam* camera);
  vec2 arcball_mouse_angle();
  void arcball_viewport_angle(Cam* camera, vec2 angle);

private:
  Dimension* dimManager;
};

#endif
