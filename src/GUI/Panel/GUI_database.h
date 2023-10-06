#ifndef GUI_DATABASE_H
#define GUI_DATABASE_H

#include <Specific/common.h>

class GUI_node;
class VK_param;
class GUI_control;
class Database_sqlite;


class GUI_database
{
public:
  //Constructor / Destructor
  GUI_database(GUI_node* gui_node);
  ~GUI_database();

public:
  //Main functions
  void design_panel();

  //Subfunction
  void design_database();
  void display_option();
  void display_data();

private:
  Database_sqlite* database;

  string path_database;
};

#endif
