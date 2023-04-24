#ifndef LOADER_H
#define LOADER_H

#include "../common.h"

class PLY_importer;


class Loader
{
public:
  //Constructor / Destructor
  Loader();
  ~Loader();

public:
  //Main functions
  Cloud* load_cloud(string path);

  //Subfunctions
  bool is_file_exist(std::string path);

private:
  PLY_importer* plyManager;
};

#endif
