#include "XYZ_importer.h"

#include <fstream>


//Constructor / Destructor
XYZ_importer::XYZ_importer(){}
XYZ_importer::~XYZ_importer(){}

//Main function
Data_file* XYZ_importer::Loader(string filePath){
  Data_file* data = new Data_file();
  //---------------------------

  //Open file
  std::ifstream infile(filePath);

  //Retrieve data
  std::string line;
  float a, b, c, d, e, f;
  while (std::getline(infile, line)){
    std::istringstream iss(line);
    iss >> a >> b >> c >> d >> e >> f;

    //Data extraction
    data->xyz.push_back(vec3(a, b, c));
    data->rgb.push_back(vec4(d, e, f, 1));
  }

  //---------------------------
  return data;
}
