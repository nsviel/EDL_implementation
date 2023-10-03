#ifndef GUI_DATABASE_H
#define GUI_DATABASE_H

#include "../../common.h"
#include "../../../../extern/database/sqlite3.h"

class Node_gui;
class VK_param;
class GUI_control;


class GUI_database
{
public:
  //Constructor / Destructor
  GUI_database(Node_gui* node_gui);
  ~GUI_database();

public:
  //Main functions
  void design_panel();

  //Subfunction
  void design_database();
  void display_option();
  void display_data();

  //Database function
  void create_table(string name);
  void remove_table(string name);
  vector<string> retrieve_all_table();

  //WIP
  void open_database();
  void close_database();
  void insert();
  void select();

private:
  sqlite3 *db;
  string path_database;
};

#endif
