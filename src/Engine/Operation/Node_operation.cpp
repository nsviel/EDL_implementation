#include "Node_operation.h"

#include "Color/Color.h"
#include "Color/Heatmap.h"
#include "Transformation/Attribut.h"

#include "../Engine.h"


//Constructor / Destructor
Node_operation::Node_operation(Engine* engine){
  //---------------------------

  this->heatmapManager = new Heatmap();
  this->colorManager = new Color(this);
  this->attributManager = new Attribut();

  //---------------------------
}
Node_operation::~Node_operation(){}
