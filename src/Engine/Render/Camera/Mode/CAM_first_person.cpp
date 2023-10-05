#include "CAM_first_person.h"
#include "../../Render_node.h"

#include <Window/Window.h>


//Constructor / Destructor
CAM_first_person::CAM_first_person(Render_node* render_node){
  //---------------------------

  this->window = render_node->get_window();

  this->mouse_pose_old = vec2(0.0f);

  //---------------------------
}
CAM_first_person::~CAM_first_person(){}

mat4 CAM_first_person::fp_view_mat(Struct_camera* camera){
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

  camera->mat_view = cam_view;

  //---------------------------
  return cam_view;
}
void CAM_first_person::fp_cam_mouse(Struct_camera* camera){
  //---------------------------

  float& azimuth = camera->angle_azimuth;
  float& elevation = camera->angle_elevation;

  //Cursor movement
  vec2 mouse_pose = window->get_mouse_pose();
  vec2 window_center = window->get_window_center();

  if(mouse_pose != mouse_pose_old){
    window->set_mouse_pose(window_center);

    // Compute new orientation
    azimuth += camera->speed_mouse * float(window_center.x - mouse_pose.x);
    elevation += camera->speed_mouse * float(window_center.y - mouse_pose.y);

    //Limites of camera rotation
    if(elevation > M_PI/2) elevation = M_PI/2;
    if(elevation < -M_PI/2) elevation = -M_PI/2;
    if(azimuth > M_PI*2) azimuth = 0;
    if(azimuth < -M_PI*2) azimuth = 0;

    //Setup mouse
    mouse_pose_old = mouse_pose;
  }

  //---------------------------
}
