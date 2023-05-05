#include "CAM_proj.h"

#include "../../Dimension/Dimension.h"
#include "../../Node_engine.h"


//Constructor / Destructor
CAM_proj::CAM_proj(Node_engine* node_engine){
  //---------------------------

  this->dimManager = node_engine->get_dimManager();

  //---------------------------
}
CAM_proj::~CAM_proj(){}

//Main function
mat4 CAM_proj::compute_proj_perspective(Cam* camera){
  Tab* tab_rendering = dimManager->get_tab("rendering");
  //---------------------------

  float z_near = camera->clip_near;
  float z_far = camera->clip_far;
  float fov = glm::radians(camera->fov);
  float ratio = (float)tab_rendering->dim.x / (float)tab_rendering->dim.y;

  mat4 cam_proj = perspective(fov, ratio, z_near, z_far);
  cam_proj[1][1] *= -1; // Because glm is designed for OpenGL convention

  //---------------------------
  return cam_proj;
}
mat4 CAM_proj::compute_proj_ortho(Cam* camera){
  //---------------------------

  float z_near = camera->clip_near;
  float z_far = camera->clip_far;
  float zoom = camera->zoom;
  mat4 cam_proj = ortho(-5.f - zoom, 5.f + zoom, -5.f - zoom, 5.f + zoom, z_near, z_far);

  //---------------------------
  return cam_proj;
}
