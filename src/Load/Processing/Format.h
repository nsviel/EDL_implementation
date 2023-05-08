#ifndef FORMAT_H
#define FORMAT_H

#include "../../common.h"

class PLY_importer;


class Format
{
public:
  //Constructor / Destructor
  Format();
  ~Format();

public:

private:
  PLY_importer* ply_import;
};

#endif
