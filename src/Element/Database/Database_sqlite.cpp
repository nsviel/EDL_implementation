#include "Database_sqlite.h"


//Constructor / Destructor
Database_sqlite::Database_sqlite(string path){
  //---------------------------

  this->path_database = path;

  //---------------------------
}
Database_sqlite::~Database_sqlite(){}

//Management function
void Database_sqlite::create_table(string name){
  //---------------------------

  SQLite::Database db(path_database.c_str(), SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

  db.exec("DROP TABLE IF EXISTS " + name);
  db.exec("CREATE TABLE " + name + " (id INTEGER PRIMARY KEY, value TEXT)");

  //---------------------------
}
void Database_sqlite::remove_table(string name){
  //---------------------------

  SQLite::Database db(path_database.c_str(), SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

  db.exec("DROP TABLE IF EXISTS " + name);

  //---------------------------
}

//Retrieving function
vector<string> Database_sqlite::retrieve_all_table(){
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
