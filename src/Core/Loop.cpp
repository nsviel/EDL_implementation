#include "Loop.h"
#include "Param.h"
#include "../Engine/Node.h"

#include <Window/Window.h>


//Constructor / Destructor
Loop::Loop(){
  //---------------------------

  this->window = new Window();

  //---------------------------
}
Loop::~Loop(){}

//Main function
void Loop::main_loop(){
  Param param;
  window->create_window(param.window_dim.x, param.window_dim.y, param.window_title);
  Node node;

  //---------------------------


  node.init(window);
  node.loop();
  node.exit();
  window->destroy_window();

  //---------------------------
}
