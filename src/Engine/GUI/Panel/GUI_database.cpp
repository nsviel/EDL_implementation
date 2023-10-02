#include "GUI_database.h"
#include "../Node_gui.h"


//Constructor / Destructor
GUI_database::GUI_database(Node_gui* node_gui){
  //---------------------------

  this->open_database();
  this->create_table();
  this->insert();
  this->select();

  //---------------------------
}
GUI_database::~GUI_database(){
  //---------------------------

  this->close_database();

  //---------------------------
}

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

  //---------------------------
}
void GUI_database::close_database(){
  //---------------------------

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
  char* error = 0;
  int rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &error);

  if( rc != SQLITE_OK ){
     fprintf(stderr, "SQL error: %s\n", error);
     sqlite3_free(error);
  } else {
     fprintf(stdout, "Table created successfully\n");
  }

  //---------------------------
}
void GUI_database::insert(){
  //---------------------------

  /* Create SQL statement */
  string sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
    "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
    "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
    "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
    "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
    "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
    "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
    "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

  /* Execute SQL statement */
  char* error = 0;
  int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &error);

  if( rc != SQLITE_OK ){
     fprintf(stderr, "SQL error: %s\n", error);
     sqlite3_free(error);
  } else {
     fprintf(stdout, "Records created successfully\n");
  }

  //---------------------------
}


static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);

   for(i = 0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }

   printf("\n");
   return 0;
}
void GUI_database::select(){
  //---------------------------

  /* Create SQL statement */
  string sql = "SELECT * from COMPANY";

  /* Execute SQL statement */
  char* error = 0;
  int rc = sqlite3_exec(db, sql.c_str(), callback, NULL, &error);

  if( rc != SQLITE_OK ) {
     fprintf(stderr, "SQL error: %s\n", error);
     sqlite3_free(error);
  } else {
     fprintf(stdout, "Operation done successfully\n");
  }

  //---------------------------
}
