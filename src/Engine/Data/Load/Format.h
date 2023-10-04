#ifndef FORMAT_H
#define FORMAT_H

#include <Specific/Struct/struct_data_file.h>
#include <string>

class PLY_importer;
class OBJ_importer;
class CSV_importer;
class PCAP_importer;
class PTS_importer;
class PTX_importer;
class XYZ_importer;


class Format
{
public:
  //Constructor / Destructor
  Format();
  ~Format();

public:
  Data_file* get_data_from_file(std::string path);

private:
  PLY_importer* ply_import;
  OBJ_importer* obj_import;
  CSV_importer* csv_import;
  PCAP_importer* pcap_import;
  PTS_importer* pts_import;
  PTX_importer* ptx_import;
  XYZ_importer* xyz_import;
};

#endif
