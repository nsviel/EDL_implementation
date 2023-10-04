#ifndef FILE_PTX_H
#define FILE_PTX_H

#include <Specific/Struct/struct_data_file.h>
#include <Specific/File/Info.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <list>


struct PTXCloud{
  //---------------------------

  //header
  glm::vec3 rootTrans;
  glm::mat3 rootRotat;
  glm::mat4 transfMat;

  //data
  std::vector<glm::vec3> location;
  std::vector<float> intensity;
  std::vector<glm::vec4> color;

  //---------------------------
};


class PTX_importer
{
public:
  //Constructor / Destructor
  PTX_importer();
  ~PTX_importer();

public:
  //Main functions
  Data_file* Loader(std::string pathFile);
  bool Exporter(std::string pathFile);

  //Subfunctions
  void Loader_header(PTXCloud* cloud);
  void Loader_data(PTXCloud* cloud);
  void Loader_assembling();
  void Loader_cloudTransformation();
  void Loader_scannerAtOrigin();

  std::string get_format_from_path(std::string path);

  inline void set_scannerAtOrigin(bool value){this->option_scannerAtOrigin = value;}
  inline void set_applyCloudTransfo(bool value){this->option_applyCloudTransfo = value;}
  inline void set_separateCloud(bool value){this->option_separateCloud = value;}
  inline void set_IdataFormat(int value){this->IdataFormat = value;}
  inline void set_retrievingIntensity(bool value){this->retrieve_I = value;}
  inline void set_retrievingColor(bool value){this->retrieve_RGB = value;}
  inline void set_retrievingNormal(bool value){this->retrieve_N = value;}
  inline void set_notUseZValue(bool value){this->option_notUseZValue = value;}

private:
  //Datatypes
  Data_file* data;

  std::list<PTXCloud*>* list_ptxCloud;
  float x, y, z, I, r, g ,b;
  bool option_separateCloud;
  bool option_scannerAtOrigin;
  bool option_applyCloudTransfo;
  bool option_notUseZValue;
  bool retrieve_I, retrieve_RGB, retrieve_N;
  int PC_line;
  int IdataFormat;
};

#endif
