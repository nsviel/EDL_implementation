#ifndef CAM_PROJ_H
#define CAM_PROJ_H

#include "../struct_cam.h"
#include "../../../common.h"

class Node_engine;
class Dimension;


class CAM_proj
{
public:
  CAM_proj(Node_engine* node_engine);
  ~CAM_proj();

public:

private:
  Dimension* dimManager;
};

#endif
