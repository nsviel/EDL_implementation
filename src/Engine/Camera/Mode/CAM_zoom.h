#ifndef CAM_ZOOM_H
#define CAM_ZOOM_H

#include "../struct_cam.h"
#include "../../../common.h"

class Node_engine;
class Dimension;


class CAM_zoom
{
public:
  CAM_zoom(Node_engine* node_engine);
  ~CAM_zoom();

public:
  mat4 fps_view_mat();
  void fps_cam_mouse();

private:
  Dimension* dimManager;

  Cam* camera;
  vec2 mouse_pose_old;
};

#endif
