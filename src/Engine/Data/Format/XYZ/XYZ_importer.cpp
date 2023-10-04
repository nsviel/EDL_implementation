#include "XYZ_importer.h"


//Constructor / Destructor
XYZ_importer::XYZ_importer(){}
XYZ_importer::~XYZ_importer(){}

//Main function
Data_file* XYZ_importer::Loader(std::string path){
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
    data->xyz.push_back(glm::vec3(a, b, c));
    data->rgb.push_back(glm::vec4(d, e, f, 1));
  }

  //---------------------------
  return data;
}
