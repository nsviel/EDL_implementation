#ifndef NODE_LOAD_H
#define NODE_LOAD_H

#include "../common.h"

class Node_engine;
class Loader;


class Node_load
{
public:
  //Constructor / Destructor
  Node_load(Node_engine* Node_engine);
  ~Node_load();

public:
  inline Loader* get_loaderManager(){return loaderManager;}

private:
  Loader* loaderManager;
};

#endif
