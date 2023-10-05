#include "CAM_proj.h"

#include "../../../../Element/Window/Dimension.h"
#include "../../Render_node.h"


//Constructor / Destructor
CAM_proj::CAM_proj(Render_node* core_node){
  //---------------------------

  this->dimManager = core_node->get_dimManager();

  //---------------------------
}
CAM_proj::~CAM_proj(){}

//Main function
mat4 CAM_proj::compute_proj_perspective(Struct_camera* camera){
  Tab* tab_rendering = dimManager->get_tab("rendering");
  //---------------------------

  float z_near = camera->clip_near;
  float z_far = camera->clip_far;
  float fov = glm::radians(camera->fov);
  float ratio = (float)tab_rendering->dim.x / (float)tab_rendering->dim.y;

  mat4 cam_proj = perspective(fov, ratio, z_near, z_far);
  cam_proj[1][1] *= -1; // Because glm is designed for OpenGL convention

  camera->mat_proj = cam_proj;

  //---------------------------
  return cam_proj;
}
mat4 CAM_proj::compute_proj_ortho(Struct_camera* camera){
  //---------------------------

  float z_near = camera->clip_near;
  float z_far = camera->clip_far;
  float zoom = camera->zoom;
  mat4 cam_proj = ortho(-5.f - zoom, 5.f + zoom, -5.f - zoom, 5.f + zoom, z_near, z_far);
  cam_proj[1][1] *= -1; // Because glm is designed for OpenGL convention

  camera->mat_proj = cam_proj;

  //---------------------------
  return cam_proj;
}
