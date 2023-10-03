#include "GUI_database.h"
#include "../Node_gui.h"
#include <SQLiteCpp/SQLiteCpp.h>

static int display_table(void *data, int argc, char **argv, char **azColName){
  //---------------------------

  fprintf(stderr, "%s: ", (const char*)data);

  for(int i=0; i<argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }

  printf("\n");

  //---------------------------
  return 0;
}


//Constructor / Destructor
GUI_database::GUI_database(Node_gui* node_gui){
  //---------------------------


  this->path_database = "../media/database/database.db3";

  this->open_database();
  /*this->create_table();
  this->insert();
  this->select();*/


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
      this->create_table(string(new_table));
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

  vector<string> vec_table = retrieve_all_table();

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

//Sqlite function
void GUI_database::create_table(string name){
  //---------------------------

  SQLite::Database db(path_database.c_str(), SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

  db.exec("DROP TABLE IF EXISTS " + name);
  db.exec("CREATE TABLE " + name + " (id INTEGER PRIMARY KEY, value TEXT)");

  //---------------------------
}
void GUI_database::remove_table(string name){
  //---------------------------

  SQLite::Database db(path_database.c_str(), SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

  db.exec("DROP TABLE IF EXISTS " + name);

  //---------------------------
}
vector<string> GUI_database::retrieve_all_table(){
  //---------------------------

  SQLite::Database db(path_database.c_str(), SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

  SQLite::Statement query(db, "SELECT * FROM sqlite_master where type='table'");
  vector<string> vec_table;
  while (query.executeStep()){
    vec_table.push_back(query.getColumn(1));
  }

  //---------------------------
  return vec_table;
}

//WIP
void GUI_database::open_database(){
  //---------------------------

  // Open a database file in create/write mode
  SQLite::Database db(path_database.c_str(), SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

  // Create a new table with an explicit "id" column aliasing the underlying rowid
  db.exec("DROP TABLE IF EXISTS test");
  db.exec("CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT)");

  // first row
  int nb = db.exec("INSERT INTO test VALUES (NULL, \"test\")");
  std::cout << "INSERT INTO test VALUES (NULL, \"test\")\", returned " << nb << std::endl;

  // second row
  nb = db.exec("INSERT INTO test VALUES (NULL, \"second\")");
  std::cout << "INSERT INTO test VALUES (NULL, \"second\")\", returned " << nb << std::endl;

  // update the second row
  nb = db.exec("UPDATE test SET value=\"second-updated\" WHERE id='2'");
  std::cout << "UPDATE test SET value=\"second-updated\" WHERE id='2', returned " << nb << std::endl;

  // Check the results : expect two row of result
  SQLite::Statement   query(db, "SELECT * FROM test");
  std::cout << "SELECT * FROM test :\n";
  while (query.executeStep())
  {
      std::cout << "row (" << query.getColumn(0) << ", \"" << query.getColumn(1) << "\")\n";
  }

  db.exec("DROP TABLE test");


  //---------------------------
}
void GUI_database::close_database(){
  //---------------------------

  sqlite3_close(db);

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
void GUI_database::select(){
  //---------------------------

  /* Create SQL statement */
  string sql = "SELECT * from COMPANY";

  /* Execute SQL statement */
  char* error = 0;
  int rc = sqlite3_exec(db, sql.c_str(), display_table, NULL, &error);

  if( rc != SQLITE_OK ) {
     fprintf(stderr, "SQL error: %s\n", error);
     sqlite3_free(error);
  } else {
     fprintf(stdout, "Operation done successfully\n");
  }



  sqlite3_stmt* stmt;
  sqlite3_prepare(db, sql.c_str(), sizeof(sql), &stmt, NULL);

  bool done = false;
  int bytes;
  int row = 0;
  const unsigned char* text;
  while (!done) {
    printf("In select while\n");
    switch (sqlite3_step (stmt)) {
    case SQLITE_ROW:
      bytes = sqlite3_column_bytes(stmt, 0);
      text  = sqlite3_column_text(stmt, 1);
      printf ("count %d: %s (%d bytes)\n", row, text, bytes);
      row++;
      break;

    case SQLITE_DONE:
      done = true;
      break;

    default:
      fprintf(stderr, "Failed.\n");
    }
  }

  //---------------------------
}
