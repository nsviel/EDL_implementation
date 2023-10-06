#ifndef LOOP_H
#define LOOP_H

class Window;
class Engine;
class GUI_node;


class Loop
{
public:
  //Constructor / Destructor
  Loop();
  ~Loop();

public:
  //Main functions
  void main_loop();

private:
  Engine* engine;
  Window* window;
  GUI_node* gui_node;
};

#endif
