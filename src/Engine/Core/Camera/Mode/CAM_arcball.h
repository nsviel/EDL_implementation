#ifndef CAM_ARCBALL_H
#define CAM_ARCBALL_H

#include "../struct_camera.h"
#include "../../Core_common.h"

class Core_node;
class Dimension;


class CAM_arcball
{
public:
  CAM_arcball(Core_node* core_node);
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
