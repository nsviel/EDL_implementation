#ifndef PLY_EXPORTER_H
#define PLY_EXPORTER_H

#include "../../../common.h"


class PLY_exporter
{
public:
  //Constructor / Destructor
  PLY_exporter();
  ~PLY_exporter();

public:
  //Main functions
  bool export_cloud(Cloud* cloud, string path_dir, string ply_format);

private:
  //Exporter subfunctions


private:
  Data_file* data_out;

  //Parametrization
  vector<string> property_type;
  vector<string> property_name;
  vector<int> property_size;
  string format;
  bool is_timestamp;
  bool is_intensity;
  bool is_normal;
  bool is_color;
  int point_data_idx;
  int point_number;
  int face_number;
  int property_number;
  int header_size;
};

#endif
