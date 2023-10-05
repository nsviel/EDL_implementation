#ifndef CAM_FPS_H
#define CAM_FPS_H

#include "../struct_camera.h"
#include "../../Render_common.h"

class Render_node;
class Dimension;


class CAM_first_person
{
public:
  CAM_first_person(Render_node* core_node);
  ~CAM_first_person();

public:
  mat4 fp_view_mat(Struct_camera* camera);
  void fp_cam_mouse(Struct_camera* camera);

private:
  Dimension* dimManager;

  vec2 mouse_pose_old;
};

#endif
