#ifndef FORMAT_H
#define FORMAT_H

#include "../../Specific/File/Info.h"
#include "../../common.h"

class PLY_importer;
class File_obj;


class Format
{
public:
  //Constructor / Destructor
  Format();
  ~Format();

public:
  Data_file* get_data_from_file(string path);

private:
  PLY_importer* ply_import;
  File_obj* obj_import;
};

#endif
