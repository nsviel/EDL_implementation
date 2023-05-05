#ifndef CAM_VIEW_H
#define CAM_VIEW_H

#include "../struct_cam.h"
#include "../../../common.h"

class Node_engine;
class Dimension;


class CAM_view
{
public:
  CAM_view(Node_engine* node_engine);
  ~CAM_view();

public:

private:
  Dimension* dimManager;
};

#endif
