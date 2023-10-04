#ifndef CSV_IMPORTER_H
#define CSV_IMPORTER_H

#include <Specific/Struct/struct_data_file.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>


class CSV_importer
{
public:
  //Constructor / Destructor
  CSV_importer();
  ~CSV_importer();

public:
  Data_file* Loader(std::string pathFile);

private:
  //Datatypes
  Data_file* data_out;
};

#endif
