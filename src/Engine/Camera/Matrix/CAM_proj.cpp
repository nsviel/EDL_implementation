#include "CAM_proj.h"

#include "../../Dimension/Dimension.h"
#include "../../Node_engine.h"


//Constructor / Destructor
CAM_proj::CAM_proj(Node_engine* node_engine){
  //---------------------------

  this->dimManager = node_engine->get_dimManager();

  //---------------------------
}
CAM_proj::~CAM_proj(){}

//Main function
