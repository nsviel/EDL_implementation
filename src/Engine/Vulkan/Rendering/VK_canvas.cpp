#include "VK_canvas.h"

#include "../Engine.h"
#include "../Data/VK_buffer.h"
#include "../Data/VK_data.h"


//Constructor / Destructor
VK_canvas::VK_canvas(Engine* engineManager){
  //---------------------------

  this->vk_buffer = engineManager->get_vk_buffer();
  this->vk_data = engineManager->get_vk_data();

  //---------------------------
}
VK_canvas::~VK_canvas(){}

//Main function
void VK_canvas::create_canvas(){
  Object* canvas_obj = new Object();
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

  canvas_obj->name = "canvas";
  canvas_obj->xyz = xyz;
  canvas_obj->uv = uv;
  canvas_obj->draw_type_name = "triangle";

  this->canvas = new Struct_data();
  this->canvas->object = canvas_obj;

  vk_data->check_for_attribut(canvas);
  vk_buffer->create_buffer(canvas);

  canvas_obj->path_texture = "../media/statue.jpg"

  //---------------------------
}
void VK_canvas::cleanup(){
  //---------------------------

  vk_buffer->clean_data(canvas);

  //---------------------------
}
