#ifndef DATABASE_SQLITE_H
#define DATABASE_SQLITE_H

#include <string>
#include <vector>
#include <SQLiteCpp/SQLiteCpp.h>

using namespace std;


class Database_sqlite
{
public:
  //Constructor / Destructor
  Database_sqlite(string path);
  ~Database_sqlite();

public:
  //Management function
  void create_table(string name);
  void remove_table(string name);

  //Retrieving function
  vector<string> retrieve_all_table();

private:
  string path_database;
};

#endif
