#ifndef NODE_ENGINE_H
#define NODE_ENGINE_H

class Engine_vulkan;
class Loop;
class GUI;


class Node_engine
{
public:
  //Constructor / Destructor
  Node_engine();
  ~Node_engine();

public:
  inline Engine_vulkan* get_engine_vulkan(){return engine_vulkan;}
  inline Loop* get_engine_loop(){return engine_loop;}
  inline GUI* get_guiManager(){return guiManager;}

private:
  Engine_vulkan* engine_vulkan;
  Loop* engine_loop;
  GUI* guiManager;
};

#endif
