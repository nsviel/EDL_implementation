#ifndef CAMERA_H
#define CAMERA_H

#include "struct_cam.h"

#include "../../common.h"

class Node_engine;
class Dimension;
class CAM_arcball;
class CAM_fps;
class CAM_zoom;


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

  //Zoom
  void compute_zoom_optic(float value);
  void compute_zoom_position(float value);

  //Camera mode
  void set_mode_projection(int value);
  void set_mode_angle(int value);
  void set_mode_view(int value);

  inline void set_desiredViewMatrix(mat4 value){camera->cam_pose_mat = value;}
  inline void set_desiredPoseON(bool value){camera->cam_pose = value;}
  inline void set_cameraFOV(float value){camera->fov = value;}
  inline void set_cameraSpeed(float value){camera->speed_move = value;}
  inline void set_cameraPos(vec3 value){camera->cam_P = value;}
  inline void set_camForward(vec3 value){camera->cam_F = value;}
  inline void set_angle_azimuth(float value){camera->angle_azimuth = value;}

  inline mat4 get_cam_view(){return compute_cam_view();}
  inline mat4 get_cam_proj(){return compute_cam_proj();}
  inline mat4 get_mvpMatrix(){return compute_cam_mvp();}
  inline float* get_angle_azimuth(){return &camera->angle_azimuth;}
  inline float get_angle_elevati(){return camera->angle_elevation;}
  inline float get_fov(){return camera->fov;}
  inline vec3 get_cam_P(){return camera->cam_P;}
  inline vec3 get_cam_target(){return camera->cam_P + camera->cam_F;}
  inline vec3 get_cam_F(){return camera->cam_F;}
  inline vec3 get_cam_U(){return camera->cam_U;}
  inline vec3 get_cam_R(){return camera->cam_R;}
  inline vec3* get_cam_COM(){return &camera->cam_COM;}
  inline vec3* get_cam_PPtr(){return &camera->cam_P;}
  inline Cam* get_camera(){return camera;}
  inline bool is_cameraMovON(){return camera->cam_move;}

private:
  Dimension* dimManager;
  CAM_arcball* cam_arcball;
  CAM_fps* cam_fps;
  CAM_zoom* cam_zoom;


  Cam* camera;
  vec2 mouse_pose_old;
};

#endif
