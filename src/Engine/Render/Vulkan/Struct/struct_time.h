#ifndef STRUCT_TIME_H
#define STRUCT_TIME_H

#include <Specific/common.h>


struct Struct_time{
  //---------------------------

  float engine_init;

  vector<float> engine_fps;
  vector<float> draw_frame;
  vector<float> renderpass_scene;
  vector<float> renderpass_edl;
  vector<float> renderpass_psr;
  vector<float> renderpass_ui;

  //---------------------------
};


#endif
