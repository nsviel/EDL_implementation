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
  inline list<Set*>* get_list_data(){return list_data;}
  inline list<Set*>* get_list_glyph(){return list_glyph;}

private:
  list<Set*>* list_data;
  list<Set*>* list_glyph;
};

#endif