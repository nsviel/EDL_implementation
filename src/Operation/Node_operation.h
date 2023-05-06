#ifndef NODE_OPERATION_H
#define NODE_OPERATION_H

#include "../common.h"

class Node;
class Heatmap;
class Color;


class Node_operation
{
public:
  //Constructor / Destructor
  Node_operation(Node* node);
  ~Node_operation();

public:
  inline Heatmap* get_heatmapManager(){return heatmapManager;}
  inline Color* get_colorManager(){return colorManager;}

private:
  Heatmap* heatmapManager;
  Color* colorManager;
};

#endif
