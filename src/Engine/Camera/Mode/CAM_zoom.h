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
  void compute_zoom_optic(Cam* camera, float value);
  void compute_zoom_position(Cam* camera, float value);

private:
  Dimension* dimManager;
};

#endif
