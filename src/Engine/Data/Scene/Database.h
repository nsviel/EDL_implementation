#ifndef DATABASE_H
#define DATABASE_H

#include "../../common.h"

class Node_data;


class Database
{
public:
  //Constructor / Destructor
  Database(Node_data* node_data);
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
