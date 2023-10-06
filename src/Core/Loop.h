#ifndef LOOP_H
#define LOOP_H

class Window;
class UI_loop;
class Engine;


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
  UI_loop* ui_loop;
};

#endif
