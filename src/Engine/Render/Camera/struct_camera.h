#ifndef STRUCT_CAMERA_H
#define STRUCT_CAMERA_H

#include <glm/glm.hpp>
#include <string>


struct Struct_camera{

  Struct_camera();
  void reset();

  glm::vec2 pos = glm::vec2(0.0f);
  glm::vec2 dim = glm::vec2(0.0f);

  glm::vec3 cam_F = glm::vec3(0.0f); // Front
  glm::vec3 cam_R = glm::vec3(0.0f); // Right
  glm::vec3 cam_U = glm::vec3(0.0f); // Up
  glm::vec3 cam_P = glm::vec3(0.0f); // Pose
  glm::vec3 cam_COM = glm::vec3(0.0f);
  glm::vec3 cam_COM_obj = glm::vec3(0.0f);

  float angle_azimuth;
  float angle_elevation;

  float fov = 0;
  float speed_mouse;
  float speed_move;
  float zoom = 0;
  float clip_near;
  float clip_far;

  std::string projection;
  std::string view;
  std::string mode;

  bool cam_move = false;
  bool cam_pose = false;
  glm::mat4 cam_pose_mat = glm::mat4(1);
  glm::mat4 mat_proj = glm::mat4(1);
  glm::mat4 mat_view = glm::mat4(1);
  glm::mat4 mat_vp = glm::mat4(1);
};

#endif
