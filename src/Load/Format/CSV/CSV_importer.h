#ifndef CSV_IMPORTER_H
#define CSV_IMPORTER_H

#include "../../../common.h"


class CSV_importer
{
public:
  //Constructor / Destructor
  CSV_importer();
  ~CSV_importer();

public:
  vector<Data_file*> Loader(string pathFile);

private:
  //Datatypes
  Data_file* data_out;
};

#endif
