#include "Database.h"

#include "../Node_data.h"


//Constructor / Destructor
Database::Database(Node_data* node_data){
  //---------------------------

  this->list_data = new list<Set*>();
  this->list_glyph = new list<Set*>();

  //---------------------------
}
Database::~Database(){}
