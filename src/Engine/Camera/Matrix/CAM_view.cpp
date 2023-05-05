#include "CAM_view.h"

#include "../../Dimension/Dimension.h"
#include "../../Node_engine.h"


//Constructor / Destructor
CAM_view::CAM_view(Node_engine* node_engine){
  //---------------------------

  this->dimManager = node_engine->get_dimManager();

  //---------------------------
}
CAM_view::~CAM_view(){}

//Main function
