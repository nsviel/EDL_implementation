#ifndef VK_CANVAS_H
#define VK_CANVAS_H

#include "../../../common.h"

class Engine;
class VK_buffer;


class VK_canvas
{
public:
  //Constructor / Destructor
  VK_canvas(Engine* engineManager);
  ~VK_canvas();

public:
  //Main functions
  void gen_canvas();

  inline Object* get_canvas(){return canvas;}

private:
  VK_buffer* vk_buffer;

  Object* canvas;
};

#endif
