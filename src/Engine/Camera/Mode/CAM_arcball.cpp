#include "CAM_arcball.h"
#include <Render/Render_node.h>

#include <Window/Window.h>


//Constructor / Destructor
CAM_arcball::CAM_arcball(Render_node* render_node){
  //---------------------------

  this->window = render_node->get_window();

  //---------------------------
}
CAM_arcball::~CAM_arcball(){}

//Main function
mat4 CAM_arcball::arcball_view_mat(Struct_camera* camera){
  mat4 cam_view;
  //---------------------------

  //Compute camera
  camera->cam_F = camera->cam_COM_obj - camera->cam_P;
  camera->cam_U = normalize(cross(camera->cam_R, camera->cam_F));

  //Compute view matrix
  cam_view = lookAt(camera->cam_P, camera->cam_COM_obj, camera->cam_U);

  //---------------------------
  return cam_view;
}
void CAM_arcball::arcball_cam_mouse(Struct_camera* camera){
  //---------------------------

  vec2 angle = arcball_mouse_angle();
  this->arcball_viewport_angle(camera, angle);

  //---------------------------
}

//Subfunction
vec2 CAM_arcball::arcball_mouse_angle(){
  //---------------------------

  vec2 mouse_pose = window->get_mouse_pose();
  window->set_mouse_pose(window->get_window_center());

  // step 1 : Calculate the amount of rotation given the mouse movement.
  vec2 window_dim = window->get_window_dim();
  vec2 window_center = window->get_window_center();
  float deltaAngleX = (2 * M_PI / window_dim.x); // a movement from left to right = 2*PI = 360 deg
  float deltaAngleY = (M_PI / window_dim.y);  // a movement from top to bottom = PI = 180 deg
  float xAngle = float(window_center.x - mouse_pose.x) * deltaAngleX * 0.1;
  float yAngle = float(window_center.y - mouse_pose.y) * deltaAngleY * 0.1;
  vec2 angle = vec2(xAngle, yAngle);

  //---------------------------
  return angle;
}
void CAM_arcball::arcball_viewport_angle(Struct_camera* camera, vec2 angle){
  //---------------------------

  // Get the homogenous position of the camera and pivot point
  vec4 cam_P (camera->cam_P.x, camera->cam_P.y, camera->cam_P.z, 1);
  vec4 cam_COM_obj (camera->cam_COM_obj.x, camera->cam_COM_obj.y, camera->cam_COM_obj.z, 1);
  vec4 cam_R (camera->cam_R.x, camera->cam_R.y, camera->cam_R.z, 1);

  // step 2: Rotate the camera around the pivot point on the first axis.
  mat4x4 Rz(1.0f);
  Rz = glm::rotate(Rz, angle.x, vec3(0, 0, 1));
  cam_P  = (Rz * (cam_P - cam_COM_obj)) + cam_COM_obj;
  camera->cam_R = Rz * cam_R;

  // step 3: Rotate the camera around the pivot point on the second axis.
  mat4x4 Rr(1.0f);
  Rr = glm::rotate(Rr, angle.y, camera->cam_R);
  camera->cam_P = (Rr * (cam_P - cam_COM_obj)) + cam_COM_obj;

  //---------------------------
}
