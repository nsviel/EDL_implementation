#ifndef PTS_IMPORTER_H
#define PTS_IMPORTER_H

#include "../../../common.h"

#include <iomanip>
#include <fstream>


class PTS_importer
{
public:
  //Constructor / Destructor
  PTS_importer();
  ~PTS_importer();

public:
  //Main functions
  Data_file* Loader(string pathFile);
  Data_file* Loader(string pathFile, int lmin, int lmax);

  bool Exporter(string pathFile, Object* object);

  inline void set_IdataFormat(int value){this->IdataFormat = value;}
  inline void set_retrievingIntensity(bool value){this->retrieve_I = value;}
  inline void set_retrievingColor(bool value){this->retrieve_RGB = value;}
  inline void set_retrievingNormal(bool value){this->retrieve_N = value;}

private:
  //Subfunctions
  void Loader_init();
  void Loader_nbColumns();
  void Loader_configuration();
  void Loader_data(Data_file* data_out, int FILE_config);

  //Loader sub-functions
  bool check_header(string pathFile);
  int check_configuration(string pathFile);
  int check_size(string pathFile, bool FILE_hasHeader);

private:
  //Variables
  int config;
  int nbptMax;
  int FILE_size, FILE_config;
  bool endHeader, FILE_hasHeader;
  bool endParameters;
  bool hasColor;
  bool hasIntensity;
  bool hasNormal;
  vector<float> line_columns;
  vector<string> dataFormat;
  string line;

  //Parameters
  int IdataFormat, export_IdataFormat;
  bool retrieve_I, retrieve_RGB, retrieve_N;
};

#endif
