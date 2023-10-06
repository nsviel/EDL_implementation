#ifndef CAM_ARCBALL_H
#define CAM_ARCBALL_H

#include "../struct_camera.h"
#include "../../Render/Render_common.h"

class Render_node;
class Window;


class CAM_arcball
{
public:
  CAM_arcball(Render_node* render_node);
  ~CAM_arcball();

public:
  mat4 arcball_view_mat(Struct_camera* camera);
  void arcball_cam_mouse(Struct_camera* camera);
  vec2 arcball_mouse_angle();
  void arcball_viewport_angle(Struct_camera* camera, vec2 angle);

private:
  Window* window;
};

#endif
