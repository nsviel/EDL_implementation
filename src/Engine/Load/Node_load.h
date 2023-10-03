#ifndef NODE_LOAD_H
#define NODE_LOAD_H

#include "../common.h"

class Engine;
class Node_engine;
class Node_data;

class Loader;


class Node_load
{
public:
  //Constructor / Destructor
  Node_load(Engine* engine);
  ~Node_load();

public:
  void loop();

  inline Node_engine* get_node_engine(){return node_engine;}
  inline Node_data* get_node_data(){return node_data;}

  inline Loader* get_loaderManager(){return loaderManager;}

private:
  Node_engine* node_engine;
  Node_data* node_data;

  Loader* loaderManager;
};


#endif
