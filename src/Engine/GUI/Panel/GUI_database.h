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
  void open_database();
  void close_database();
  void design_table();
  void create_table();
  void insert();
  void select();

private:
  sqlite3 *db;
};

#endif
