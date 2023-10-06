#include "GUI_database.h"
#include <GUI.h>
#include <Database/Database_sqlite.h>


//Constructor / Destructor
GUI_database::GUI_database(GUI* gui){
  //---------------------------

  this->database = new Database_sqlite("../media/database/database.db3");
  this->path_database = "../media/database/database.db3";

  //---------------------------
}
GUI_database::~GUI_database(){}

//Main function
void GUI_database::design_panel(){
  //---------------------------

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(500, 500));
  ImGui::Begin("Database");
  this->design_database();
  ImGui::End();
  ImGui::PopStyleVar();

  //---------------------------
}

//Subfunction
void GUI_database::design_database(){
  //---------------------------

  this->display_option();
  this->display_data();

  //---------------------------
}
void GUI_database::display_option(){
  //---------------------------

  ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_Borders;
  flags |= ImGuiTableFlags_SizingFixedFit;

  if(ImGui::BeginTable("database_option", 2, flags)){
    ImGui::TableSetupColumn("one");
    ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthFixed, 100.0f);

    //ADD table
    ImGui::TableNextColumn();
    ImGui::SetNextItemWidth(150);
    static char new_table[256];
    ImGui::InputText("##111", new_table, IM_ARRAYSIZE(new_table));
    ImGui::TableNextColumn();
    if(ImGui::Button("ADD table", ImVec2(100, 0.0f))){
      database->create_table(string(new_table));
    }

    ImGui::TableNextRow();

    //ADD data
    ImGui::TableNextColumn();
    ImGui::SetNextItemWidth(150);
    static char new_data[256];
    ImGui::InputText("##112", new_data, IM_ARRAYSIZE(new_data));
    ImGui::TableNextColumn();
    ImGui::Button("ADD data", ImVec2(100, 0.0f));

    ImGui::EndTable();
  }

  //---------------------------
}
void GUI_database::display_data(){
  //---------------------------

  vector<string> vec_table = database->retrieve_all_table();

  //Table list combo
  static int selectedIndex = 0;
  if(ImGui::BeginCombo("table_combo", vec_table[selectedIndex].c_str())){
    for(int i = 0; i < vec_table.size(); ++i){
      const bool isSelected = (selectedIndex == i);
      if(ImGui::Selectable(vec_table[i].c_str(), isSelected)){
        selectedIndex = i;
      }

      if(isSelected){
        ImGui::SetItemDefaultFocus();
      }
    }
    ImGui::EndCombo();
  }



  ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_Borders;
  flags |= ImGuiTableFlags_RowBg;

  if(ImGui::BeginTable("database_view", 1, flags)){

    for(int i=0; i<vec_table.size(); i++){
      string& table = vec_table[i];

      ImGui::TableNextRow();
      ImGui::TableNextColumn();

      ImGui::PushID(table.c_str());
      ImGui::Text("%s", table.c_str());
      ImGui::PopID();
    }

    ImGui::EndTable();
  }



  //---------------------------
}
