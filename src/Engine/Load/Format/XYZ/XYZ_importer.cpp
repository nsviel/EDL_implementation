#include "XYZ_importer.h"

#include "../../../Specific/File/Info.h"


//Constructor / Destructor
XYZ_importer::XYZ_importer(){}
XYZ_importer::~XYZ_importer(){}

//Main function
Data_file* XYZ_importer::Loader(string path){
  Data_file* data = new Data_file();
  //---------------------------

  data->name = get_name_from_path(path);
  data->path_file = path;

  //Open file
  std::ifstream infile(path);

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
