#include "Heatmap.h"
#include "Colormap.h"

#include <Specific/Function/fct_math.h>


//Constructor / destructor
Heatmap::Heatmap(){
  //---------------------------

  this->colormapManager = new Colormap();

  this->heatmap_mode = 1;
  this->is_normalization = true;
  this->range_norm = vec2(0.0f, 1.0f);
  this->range_height = vec2(-2.0f, 2.0f);
  this->range_intensity = vec2(0.0f, 1.0f);

  //---------------------------
}
Heatmap::~Heatmap(){
  //---------------------------

  delete colormapManager;

  //---------------------------
}
