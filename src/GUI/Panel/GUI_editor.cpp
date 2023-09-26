#include "GUI_editor.h"
#include "../Node_gui.h"


//Constructor / Destructor
GUI_editor::GUI_editor(Node_gui* node_gui){
  //---------------------------

  this->editor = new TextEditor();
  editor->SetText("hello\n\nkeiuhfezkf\njzgefjez");

  //---------------------------
}
GUI_editor::~GUI_editor(){}

//Main function
void GUI_editor::design_editor(){
  //---------------------------

  editor->Render("hello");

  //---------------------------
}
