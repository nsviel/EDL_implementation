#ifndef STRUCT_TIME_H
#define STRUCT_TIME_H

#include "../../../common.h"


struct Struct_time{
  //---------------------------

  float engine_init;
  
  vector<float> engine_fps;
  vector<float> draw_frame;
  vector<float> renderpass_scene;
  vector<float> renderpass_render;
  vector<float> renderpass_ui;

  //---------------------------
};


#endif
