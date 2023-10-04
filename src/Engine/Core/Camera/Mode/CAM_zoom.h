#ifndef CAM_ZOOM_H
#define CAM_ZOOM_H

#include "../struct_camera.h"
#include "../../Core_common.h"

class Core_node;
class Dimension;


class CAM_zoom
{
public:
  CAM_zoom(Core_node* core_node);
  ~CAM_zoom();

public:
  void compute_zoom_optic(Struct_camera* camera, float value);
  void compute_zoom_position(Struct_camera* camera, float value);

private:
  Dimension* dimManager;
};

#endif
