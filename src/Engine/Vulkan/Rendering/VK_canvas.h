#ifndef VK_CANVAS_H
#define VK_CANVAS_H

#include "../Struct/struct_data.h"
#include "../../../common.h"

class Engine;
class VK_buffer;
class VK_data;


class VK_canvas
{
public:
  //Constructor / Destructor
  VK_canvas(Engine* engineManager);
  ~VK_canvas();

public:
  //Main functions
  void create_canvas();
  void cleanup();

  inline Struct_data* get_canvas(){return canvas;}

private:
  VK_buffer* vk_buffer;
  VK_data* vk_data;

  Struct_data* canvas;
};

#endif
