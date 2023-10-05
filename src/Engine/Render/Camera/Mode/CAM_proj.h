#ifndef CAM_PROJ_H
#define CAM_PROJ_H

#include "../struct_camera.h"
#include "../../Render_common.h"

class Render_node;
class Window;


class CAM_proj
{
public:
  CAM_proj(Render_node* render_node);
  ~CAM_proj();

public:
  mat4 compute_proj_perspective(Struct_camera* camera);
  mat4 compute_proj_ortho(Struct_camera* camera);

private:
  Window* window;
};

#endif
