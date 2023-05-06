#include "Node_operation.h"

#include "Color/Color.h"
#include "Color/Heatmap.h"

#include "../Node.h"


//Constructor / Destructor
Node_operation::Node_operation(Node* node){
  //---------------------------

  this->heatmapManager = new Heatmap();
  this->colorManager = new Color(this);

  //---------------------------
}
Node_operation::~Node_operation(){}
