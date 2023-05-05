#include "CAM_fps.h"

#include "../../Dimension/Dimension.h"
#include "../../Node_engine.h"


//Constructor / Destructor
CAM_fps::CAM_fps(Node_engine* node_engine){
  //---------------------------

  this->dimManager = node_engine->get_dimManager();
  this->camera = new Cam();
  this->mouse_pose_old = vec2(0.0f);

  //---------------------------
}
CAM_fps::~CAM_fps(){}

mat4 CAM_fps::fps_view_mat(){
  //---------------------------

  float azimuth = camera->angle_azimuth;
  float elevation = camera->angle_elevation;

  //Forward and Up camera
  if(camera->view == "top"){
    elevation = -M_PI/2.0f;
  }

  //Compute camera
  camera->cam_R = normalize(vec3(cos(azimuth - M_PI/2.0f), sin(azimuth - M_PI/2.0f), 0));
  camera->cam_F = vec3(cos(elevation) * cos(azimuth), cos(elevation) * sin(azimuth), sin(elevation));
  camera->cam_U = normalize(cross(camera->cam_R, camera->cam_F));
  vec3 cam_target = camera->cam_P + camera->cam_F;

  //Compute view matrix
  mat4 cam_view = lookAt(camera->cam_P, cam_target, camera->cam_U);

  //---------------------------
  return cam_view;
}
void CAM_fps::fps_cam_mouse(){
  //---------------------------

  float& azimuth = camera->angle_azimuth;
  float& elevation = camera->angle_elevation;

  //Cursor movement
  vec2 mouse_pose = dimManager->get_mouse_pose();

  if(mouse_pose != mouse_pose_old){
    dimManager->set_mouse_pose(dimManager->get_gl_middle());

    // Compute new orientation
    vec2 gl_mid = dimManager->get_gl_middle();
    azimuth += camera->speed_mouse * float(gl_mid.x - mouse_pose.x);
    elevation += camera->speed_mouse * float(gl_mid.y - mouse_pose.y);

    //Limites of camera rotation
    if(elevation > M_PI/2) elevation = M_PI/2;
    if(elevation < -M_PI/2) elevation = -M_PI/2;
    if(azimuth > M_PI*2) azimuth = 0;
    if(azimuth < -M_PI*2) azimuth = 0;

    //Setup mouse
    glfwSetInputMode(dimManager->get_window(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    mouse_pose_old = mouse_pose;
  }

  //---------------------------
}
