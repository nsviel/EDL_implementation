#include "GUI_editor_hexa.h"
#include <GUI_node.h>


//Constructor / Destructor
GUI_editor_hexa::GUI_editor_hexa(GUI_node* gui_node){
  //---------------------------


  //---------------------------
}
GUI_editor_hexa::~GUI_editor_hexa(){}

//Main function
void GUI_editor_hexa::design_panel(){
  //---------------------------


  //---------------------------
}

//Subfunction
void GUI_editor_hexa::design_editor_memory(){
  //---------------------------

  static MemoryEditor mem_edit;
  static char data[0x10000];
  size_t data_size = 0x10000;
  mem_edit.DrawWindow("Memory Editor", data, data_size);

  //---------------------------
}
