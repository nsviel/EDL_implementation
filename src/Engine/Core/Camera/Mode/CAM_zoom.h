#ifndef CAM_ZOOM_H
#define CAM_ZOOM_H

#include "../struct_camera.h"
#include "../../../common.h"

class Node_core;
class Dimension;


class CAM_zoom
{
public:
  CAM_zoom(Node_core* node_core);
  ~CAM_zoom();

public:
  void compute_zoom_optic(Struct_camera* camera, float value);
  void compute_zoom_position(Struct_camera* camera, float value);

private:
  Dimension* dimManager;
};

#endif
