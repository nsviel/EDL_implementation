#include "VK_canvas.h"

#include "../Engine.h"
#include "../Data/VK_buffer.h"


//Constructor / Destructor
VK_canvas::VK_canvas(Engine* engineManager){
  //---------------------------

  this->vk_buffer = engineManager->get_vk_buffer();

  //---------------------------
}
VK_canvas::~VK_canvas(){}

//Main function
void VK_canvas::gen_canvas(){
  this->canvas = new Object();
  //---------------------------

  //Generic quad coordinates and UV
  vector<vec3> xyz;
  xyz.push_back(vec3(-1.0f, 1.0f, 0.0f));
  xyz.push_back(vec3(-1.0f, -1.0f, 0.0f));
  xyz.push_back(vec3(1.0f, -1.0f, 0.0f));
  xyz.push_back(vec3(-1.0f, 1.0f, 0.0f));
  xyz.push_back(vec3(1.0f, -1.0f, 0.0f));
  xyz.push_back(vec3(1.0f, 1.0f, 0.0f));

  vector<vec2> uv;
  uv.push_back(vec2(0.0f,  1.0f));
  uv.push_back(vec2(0.0f,  0.0f));
  uv.push_back(vec2(1.0f,  0.0f));
  uv.push_back(vec2(0.0f,  1.0f));
  uv.push_back(vec2(1.0f,  0.0f));
  uv.push_back(vec2(1.0f,  1.0f));

  canvas->name = "canvas";
  canvas->xyz = xyz;
  canvas->uv = uv;
  canvas->draw_type_name = "triangle";

  vk_buffer->create_buffer_xyz(canvas, canvas->xyz);
  vk_buffer->create_buffer_uv(canvas, canvas->uv);

  //---------------------------
}
