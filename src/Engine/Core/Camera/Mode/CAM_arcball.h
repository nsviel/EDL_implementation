#ifndef CAM_ARCBALL_H
#define CAM_ARCBALL_H

#include "../struct_camera.h"
#include "../../../common.h"

class Node_core;
class Dimension;


class CAM_arcball
{
public:
  CAM_arcball(Node_core* node_core);
  ~CAM_arcball();

public:
  mat4 arcball_view_mat(Struct_camera* camera);
  void arcball_cam_mouse(Struct_camera* camera);
  vec2 arcball_mouse_angle();
  void arcball_viewport_angle(Struct_camera* camera, vec2 angle);

private:
  Dimension* dimManager;
};

#endif
