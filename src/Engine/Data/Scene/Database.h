#ifndef DATABASE_H
#define DATABASE_H

#include "../Data_common.h"

class Data_node;


class Database
{
public:
  //Constructor / Destructor
  Database(Data_node* data_node);
  ~Database();

public:
  inline list<Set*>* get_list_data_scene(){return list_data;}
  inline list<Set*>* get_list_data_glyph(){return list_glyph;}

private:
  int ID_obj;

  list<Set*>* list_data;
  list<Set*>* list_glyph;
};

#endif
