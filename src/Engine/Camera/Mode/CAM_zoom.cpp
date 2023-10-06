#include "CAM_zoom.h"
#include <Render/Render_node.h>


//Constructor / Destructor
CAM_zoom::CAM_zoom(Render_node* render_node){
  //---------------------------

  //---------------------------
}
CAM_zoom::~CAM_zoom(){}

void CAM_zoom::compute_zoom_optic(Struct_camera* camera, float yoffset){
  //---------------------------

  //Perspective zoom
  float camFOV = 65;
  if(camera->fov >= 1.0f && camera->fov <= camFOV) camera->fov -= yoffset;
  if(camera->fov <= 1.0f) camera->fov = 1.0f;
  if(camera->fov >= camFOV) camera->fov = camFOV;

  //Ortho zoom
  camera->zoom -= yoffset * 0.1;

  //---------------------------
}
void CAM_zoom::compute_zoom_position(Struct_camera* camera, float yoffset){
  //---------------------------

  //Perspective zoom
  vec3 cam_forwardMove = camera->cam_F * yoffset * camera->speed_move * vec3(0.1,0.1,0.1);
  camera->cam_P += cam_forwardMove;

  //Ortho zoom
  camera->zoom -= yoffset * 0.1;

  //---------------------------
}
