#include "Camera.h"
#include "Mode/CAM_first_person.h"
#include "Mode/CAM_arcball.h"
#include "Mode/CAM_zoom.h"
#include "Mode/CAM_proj.h"

#include "../Dimension/Dimension.h"
#include "../Core_node.h"
#include "../Core_param.h"

#include "../../Node.h"
#include "../../Data/Data_node.h"
#include "../../Data/Scene/Scene.h"


//Constructor / Destructor
Camera::Camera(Core_node* core_node){
  //---------------------------

  this->node = core_node->get_node();
  this->dimManager = core_node->get_dimManager();
  this->core_param = core_node->get_core_param();
  this->cam_arcball = new CAM_arcball(core_node);
  this->cam_fp = new CAM_first_person(core_node);
  this->cam_zoom = new CAM_zoom(core_node);
  this->cam_proj = new CAM_proj(core_node);

  //---------------------------
}
Camera::~Camera(){
  //---------------------------

  delete cam_arcball;
  delete cam_fp;
  delete cam_zoom;
  delete cam_proj;

  //---------------------------
}

//MVP Matrix
mat4 Camera::compute_cam_view(){
  Struct_camera* camera = &core_param->camera;
  mat4 cam_view;
  //---------------------------

  if(camera->cam_pose){
    cam_view = camera->cam_pose_mat;
  }else if(camera->mode == "first_person"){
    cam_view = cam_fp->fp_view_mat(camera);
  }else if(camera->mode == "arcball"){
    Data_node* data_node = node->get_data_node();
    Scene* sceneManager = data_node->get_sceneManager();
    Object* object = sceneManager->get_selected_object();
    if(object != nullptr) camera->cam_COM_obj = object->COM;
    cam_view = cam_arcball->arcball_view_mat(camera);
  }

  //---------------------------
  return cam_view;
}
mat4 Camera::compute_cam_proj(){
  Struct_camera* camera = &core_param->camera;
  mat4 projection;
  //---------------------------

  if(camera->projection == "perspective"){
    projection = cam_proj->compute_proj_perspective(camera);
  }
  else if(camera->projection == "orthographic"){
    projection = cam_proj->compute_proj_ortho(camera);
  }

  //---------------------------
  return projection;
}
mat4 Camera::compute_cam_mvp(){
  //---------------------------

  mat4 cam_mode = mat4(1);
  mat4 cam_view = compute_cam_view();
  mat4 cam_proj = compute_cam_proj();

  mat4 mvpMatrix = cam_proj * cam_view * cam_mode;

  //---------------------------
  return mvpMatrix;
}
mat4 Camera::compute_cam_world_pose(){
  Struct_camera* camera = &core_param->camera;
  //---------------------------

  vec3 zaxis = normalize(camera->cam_F);
  vec3 xaxis = normalize(cross(camera->cam_U, zaxis));
  vec3 yaxis = cross(zaxis, xaxis);

  mat4 absPose(
         xaxis[0], yaxis[0], zaxis[0], camera->cam_P[0],
         xaxis[1], yaxis[1], zaxis[1], camera->cam_P[1],
         xaxis[2], yaxis[2], zaxis[2], camera->cam_P[2],
           0,       0,       0,     1);

  //---------------------------
  return absPose;
}
void Camera::compute_zoom(float value){
  Struct_camera* camera = &core_param->camera;
  //---------------------------

  cam_zoom->compute_zoom_position(camera, value);

  //---------------------------
}
void Camera::input_cam_mouse(){
  Struct_camera* camera = &core_param->camera;
  //---------------------------

  if(camera->cam_move){
    if(camera->mode == "first_person"){
      cam_fp->fp_cam_mouse(camera);
      ImGui::SetMouseCursor(ImGuiMouseCursor_None);
    }else if(camera->mode == "arcball"){
      cam_arcball->arcball_cam_mouse(camera);
      ImGui::SetMouseCursor(ImGuiMouseCursor_None);
    }
  }

  //---------------------------
}

//Camera mode
void Camera::set_mode_projection(int proj){
  Struct_camera* camera = &core_param->camera;
  //---------------------------

  switch(proj){
    case 0:{ //Perspective
      camera->projection = "perspective";
      break;
    }
    case 1:{ //Orthographic
      camera->projection = "orthographic";
      break;
    }
  }

  //---------------------------
}
void Camera::set_mode_angle(int view){
  Struct_camera* camera = &core_param->camera;
  //---------------------------

  switch(view){
    case 0:{ //Top
      camera->view = "top";
      break;
    }
    case 1:{ //Oblique
      camera->view = "oblique";
      break;
    }
  }

  //---------------------------
}
void Camera::set_mode_view(int mode){
  Struct_camera* camera = &core_param->camera;
  //---------------------------

  switch(mode){
    case 0:{ //Default
      camera->mode = "first_person";
      break;
    }
    case 1:{ //Arcball
      camera->mode = "arcball";
      break;
    }
  }

  //---------------------------
}

void Camera::control(string what, bool fast){
  Struct_camera* camera = &core_param->camera;
  //---------------------------

  //Compute camera movment speed value
  float cam_speed = camera->speed_move * 0.000016;
  if(fast){
    cam_speed *= 5;
  }

  if(what == "up"){
    camera->cam_P += camera->cam_F * cam_speed;
  }
  else if(what == "down"){
    camera->cam_P -= camera->cam_F * cam_speed;
  }
  else if(what == "right"){
    if(camera->mode == "first_person"){
      camera->cam_P += camera->cam_R * cam_speed;
    }else if(camera->mode == "arcball"){
      vec2 angle =vec2(-cam_speed/10, 0);
      cam_arcball->arcball_viewport_angle(camera, angle);
    }
  }
  else if(what == "left"){
    if(camera->mode == "first_person"){
      camera->cam_P -= camera->cam_R * cam_speed;
    }else if(camera->mode == "arcball"){
      vec2 angle =vec2(cam_speed/10, 0);
      cam_arcball->arcball_viewport_angle(camera, angle);
    }
  }

  //---------------------------
}
void Camera::reset_camera(){
  Struct_camera* camera = &core_param->camera;
  //---------------------------

  camera->reset();

  //---------------------------
}
