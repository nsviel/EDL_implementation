#ifndef PTS_IMPORTER_H
#define PTS_IMPORTER_H

#include <Specific/Struct/struct_data_file.h>
#include <Specific/Struct/struct_object.h>
#include <Specific/File/Info.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>


class PTS_importer
{
public:
  //Constructor / Destructor
  PTS_importer();
  ~PTS_importer();

public:
  //Main functions
  Data_file* Loader(std::string pathFile);
  Data_file* Loader(std::string pathFile, int lmin, int lmax);

  bool Exporter(std::string pathFile, Object* object);

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
  bool check_header(std::string pathFile);
  int check_configuration(std::string pathFile);
  int check_size(std::string pathFile, bool FILE_hasHeader);

private:
  std::vector<float> line_columns;
  std::vector<std::string> dataFormat;
  std::string line;
  bool endHeader, FILE_hasHeader;
  bool endParameters;
  bool hasColor;
  bool hasIntensity;
  bool hasNormal;
  bool retrieve_I, retrieve_RGB, retrieve_N;
  int config;
  int nbptMax;
  int FILE_size, FILE_config;
  int IdataFormat, export_IdataFormat;

};

#endif
