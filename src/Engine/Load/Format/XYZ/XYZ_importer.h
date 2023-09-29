#ifndef XYZ_IMPORTER_H
#define XYZ_IMPORTER_H

#include "../../../common.h"


class XYZ_importer
{
public:
  //Constructor / Destructor
  XYZ_importer();
  ~XYZ_importer();

public:
  Data_file* Loader(string filePath);

private:
  //Datatypes
  Data_file* data_out;
};

#endif
