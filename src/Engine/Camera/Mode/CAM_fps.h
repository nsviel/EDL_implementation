#ifndef CAM_FPS_H
#define CAM_FPS_H

#include "../struct_cam.h"
#include "../../../common.h"

class Node_engine;
class Dimension;


class CAM_fps
{
public:
  CAM_fps(Node_engine* node_engine);
  ~CAM_fps();

public:
  mat4 fps_view_mat();
  void fps_cam_mouse();

private:
  Dimension* dimManager;

  Cam* camera;
  vec2 mouse_pose_old;
};

#endif
