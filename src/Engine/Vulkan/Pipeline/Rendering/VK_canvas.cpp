#include "VK_canvas.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"
#include "../../Data/VK_buffer.h"
#include "../../Data/VK_data.h"
#include "../../Data/VK_texture.h"
#include "../../Shader/Binding/VK_binding.h"


//Constructor / Destructor
VK_canvas::VK_canvas(VK_engine* vk_engine){
  //---------------------------

  this->vk_param = vk_engine->get_vk_param();
  this->vk_buffer = vk_engine->get_vk_buffer();
  this->vk_data = vk_engine->get_vk_data();
  this->vk_texture = vk_engine->get_vk_texture();
  this->vk_binding = vk_engine->get_vk_binding();

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

  vk_texture->load_texture(canvas, "../media/statue.jpg");
  canvas->binding.vec_required_binding.push_back(std::make_tuple("mvp", "mat4", 0, TYPE_UNIFORM, STAGE_VS));
  canvas->binding.vec_required_binding.push_back(std::make_tuple("texture", "", 2, TYPE_SAMPLER, STAGE_FS));
  vk_binding->fill_binding_from_requirement(canvas->binding);

  //---------------------------
}
void VK_canvas::cleanup(){
  //---------------------------

  vk_buffer->clean_buffer(canvas);
  vk_binding->clean_binding(canvas->binding);
  vk_texture->clean_texture(canvas);

  //---------------------------
}