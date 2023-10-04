#ifndef NODE_LOAD_H
#define NODE_LOAD_H

#include "../common.h"

class Node;
class Node_core;
class Node_data;

class Loader;


class Node_load
{
public:
  //Constructor / Destructor
  Node_load(Node* node);
  ~Node_load();

public:
  void loop();

  inline Node_core* get_node_core(){return node_core;}
  inline Node_data* get_node_data(){return node_data;}

  inline Loader* get_loaderManager(){return loaderManager;}

private:
  Node_core* node_core;
  Node_data* node_data;

  Loader* loaderManager;
};


#endif
