#ifndef CAMERA_H
#define CAMERA_H

#include "struct_camera.h"

#include "../Render_common.h"

class Engine;
class Render_node;
class Render_param;
class CAM_arcball;
class CAM_first_person;
class CAM_zoom;
class CAM_proj;


class Camera
{
public:
  Camera(Render_node* render_node);
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
  Engine* engine;
  Render_param* core_param;
  CAM_arcball* cam_arcball;
  CAM_first_person* cam_fp;
  CAM_zoom* cam_zoom;
  CAM_proj* cam_proj;

  vec3 arcball_origin;
};

#endif
