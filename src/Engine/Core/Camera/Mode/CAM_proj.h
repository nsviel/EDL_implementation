#ifndef CAM_PROJ_H
#define CAM_PROJ_H

#include "../struct_camera.h"
#include "../../../common.h"

class Node_engine;
class Dimension;


class CAM_proj
{
public:
  CAM_proj(Node_engine* node_engine);
  ~CAM_proj();

public:
  mat4 compute_proj_perspective(Struct_camera* camera);
  mat4 compute_proj_ortho(Struct_camera* camera);

private:
  Dimension* dimManager;
};

#endif
