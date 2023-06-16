#include "WIN_set.h"

#include "../Node_gui.h"
#include "../GUI_param.h"


//Constructor / Destructor
WIN_set::WIN_set(Node_gui* node_gui, bool* show_window, string name) : WIN_base(show_window, name){
  //---------------------------

  this->gui_param = node_gui->get_gui_param();

  this->item_width = 150;

  //---------------------------
}
WIN_set::~WIN_set(){}

//Main function
void WIN_set::design_window(){
  //---------------------------

  this->set_info(gui_param->set_selected);

  //---------------------------
}

//Subfunction
void WIN_set::set_info(Set* set){
  //---------------------------

  this->name = set->name;

  //---------------------------
}
