#ifndef CAMERA_H
#define CAMERA_H

#include "struct_camera.h"

#include "../../common.h"

class Node;
class Node_engine;
class Param_engine;
class Dimension;
class CAM_arcball;
class CAM_first_person;
class CAM_zoom;
class CAM_proj;


class Camera
{
public:
  Camera(Node_engine* node_engine);
  ~Camera();

public:
  //MVP matrices
  mat4 compute_cam_view();
  mat4 compute_cam_proj();
  mat4 compute_cam_mvp();
  mat4 compute_cam_world_pose();
  void input_cam_mouse();
  void compute_zoom(float value);

  //Camera mode
  void set_mode_projection(int value);
  void set_mode_angle(int value);
  void set_mode_view(int value);

  void control(string what, bool fast);
  void reset_camera();

  inline mat4 get_cam_view(){return compute_cam_view();}
  inline mat4 get_cam_proj(){return compute_cam_proj();}
  inline mat4 get_mvpMatrix(){return compute_cam_mvp();}

private:
  Node* node;
  Param_engine* param_engine;
  Dimension* dimManager;
  CAM_arcball* cam_arcball;
  CAM_first_person* cam_fp;
  CAM_zoom* cam_zoom;
  CAM_proj* cam_proj;
};

#endif
