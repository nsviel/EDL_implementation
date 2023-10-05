#ifndef LOOP_H
#define LOOP_H

class Window;


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
  Window* window;
};

#endif
