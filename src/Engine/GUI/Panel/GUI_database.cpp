#include "GUI_database.h"
#include "../Node_gui.h"


//Constructor / Destructor
GUI_database::GUI_database(Node_gui* node_gui){
  //---------------------------

  this->open_database();
  this->create_table();

  //---------------------------
}
GUI_database::~GUI_database(){}

//Main function
void GUI_database::design_panel(){
  //---------------------------

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(500, 500));
  ImGui::Begin("Database");
  this->design_table();
  ImGui::End();
  ImGui::PopStyleVar();

  //---------------------------
}

//Subfunction
void GUI_database::open_database(){
  //---------------------------

  int rc = sqlite3_open("../media/database/database.db", &db);
  if(rc){
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
  }else{
    fprintf(stderr, "Opened database successfully\n");
  }
  sqlite3_close(db);

  //---------------------------
}
void GUI_database::design_table(){
  //---------------------------



  //---------------------------
}
void GUI_database::create_table(){
  //---------------------------

  /* Create SQL statement */
  string sql = "CREATE TABLE COMPANY("  \
   "ID INT PRIMARY KEY     NOT NULL," \
   "NAME           TEXT    NOT NULL," \
   "AGE            INT     NOT NULL," \
   "ADDRESS        CHAR(50)," \
   "SALARY         REAL );";

  /* Execute SQL statement */
  char* zErrMsg = 0;
  int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);

  if( rc != SQLITE_OK ){
     fprintf(stderr, "SQL error: %s\n", zErrMsg);
     sqlite3_free(zErrMsg);
  } else {
     fprintf(stdout, "Table created successfully\n");
  }

  //---------------------------
}
