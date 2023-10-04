#include "Database.h"

#include "../Data_node.h"


//Constructor / Destructor
Database::Database(Data_node* data_node){
  //---------------------------

  this->ID_obj = 0;

  this->list_data = new list<Set*>();
  this->list_glyph = new list<Set*>();

  //---------------------------
}
Database::~Database(){}
