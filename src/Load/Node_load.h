#ifndef NODE_LOAD_H
#define NODE_LOAD_H

#include "../common.h"

class Node;
class Loader;


class Node_load
{
public:
  //Constructor / Destructor
  Node_load(Node* node);
  ~Node_load();

public:
  void loop();

  inline Loader* get_loaderManager(){return loaderManager;}

private:
  Loader* loaderManager;
};

#endif
