#ifndef CAM_ZOOM_H
#define CAM_ZOOM_H

#include "../struct_camera.h"
#include "../../Render_common.h"

class Render_node;


class CAM_zoom
{
public:
  CAM_zoom(Render_node* render_node);
  ~CAM_zoom();

public:
  void compute_zoom_optic(Struct_camera* camera, float value);
  void compute_zoom_position(Struct_camera* camera, float value);

private:
};

#endif
