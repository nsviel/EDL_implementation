#ifndef CAM_FPS_H
#define CAM_FPS_H

#include "../struct_cam.h"
#include "../../../common.h"

class Node_engine;
class Dimension;


class CAM_first_person
{
public:
  CAM_first_person(Node_engine* node_engine);
  ~CAM_first_person();

public:
  mat4 fp_view_mat(Cam* camera);
  void fp_cam_mouse(Cam* camera);

private:
  Dimension* dimManager;

  vec2 mouse_pose_old;
};

#endif
