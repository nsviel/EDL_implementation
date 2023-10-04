#ifndef NODE_H
#define NODE_H

#include "common.h"

class Node_core;
class Node_load;
class Node_gui;
class Node_data;


class Node
{
public:
  //Constructor / Destructor
  Node();
  ~Node();

public:
  void init();
  void loop();
  void exit();
  void reset();

  inline Node_core* get_node_core(){return node_core;}
  inline Node_load* get_node_load(){return node_load;}
  inline Node_gui* get_node_gui(){return node_gui;}
  inline Node_data* get_node_data(){return node_data;}

private:
  Node_core* node_core;
  Node_load* node_load;
  Node_gui* node_gui;
  Node_data* node_data;
};

#endif
