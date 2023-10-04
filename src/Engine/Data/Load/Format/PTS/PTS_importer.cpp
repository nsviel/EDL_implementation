#include "PTS_importer.h"


//Constructor / Destructor
PTS_importer::PTS_importer(){
  //---------------------------

  this->nbptMax = 40000000;
  this->retrieve_I = true;
  this->retrieve_RGB = true;
  this->retrieve_N = true;
  this->IdataFormat = 2;
  this->export_IdataFormat = 2;

  //---------------------------
}
PTS_importer::~PTS_importer(){}

//Main load functions
Data_file* PTS_importer::Loader(std::string path){
  Data_file* data = new Data_file();
  //---------------------------

  data->name = get_name_from_path(path);
  data->path_file = path;

  //Initialization
  this->Loader_init();
  bool FILE_hasHeader = check_header(path);
  int FILE_config = check_configuration(path);
  int FILE_size = check_size(path, FILE_hasHeader);

  //Read file
  std::ifstream infile1(path);
  while(std::getline(infile1, line))
  {
    //If line empty break the while
    if(line.empty()){
      break;
    }

    //Prevent from reading the header
    if(FILE_hasHeader){
      std::getline(infile1, line);
      FILE_hasHeader = false;
    }

    //Retrieve data
    this->Loader_data(data, FILE_config);
  }

  //---------------------------
  return data;
}
Data_file* PTS_importer::Loader(std::string path, int lmin, int lmax){
  Data_file* data = new Data_file();
  //---------------------------

  //Initialization
  this->Loader_init();
  bool FILE_hasHeader = check_header(path);
  int FILE_config = check_configuration(path);
  int FILE_size = check_size(path, FILE_hasHeader);

  //Read file
  int cpt = 0;
  std::ifstream infile1(path);
  while (std::getline(infile1, line))
  {
    if(cpt >= lmin && cpt < lmax){
      //If line empty break the while
      if(line.empty()){
        break;
      }

      //Prevent from reading the header
      if(FILE_hasHeader){
        std::getline(infile1, line);
        FILE_hasHeader = false;
      }

      //Retrieve data
      if(endParameters && endHeader){
        this->Loader_data(data, FILE_config);
      }
    }
    cpt++;
  }

  //---------------------------
  data->nb_element = cpt;
  return data;
}

//Sub load functions
void PTS_importer::Loader_init(){
  //---------------------------

  this->config = -1;
  this->endHeader = false;
  this->endParameters = false;
  this->hasColor = false;
  this->hasIntensity = false;
  this->hasNormal = false;

  //---------------------------
}
void PTS_importer::Loader_nbColumns(){
  //Extraction of each column
  bool endLoop = false;
  std::string line_loop = line;
  line_columns.clear();
  //---------------------------

  while(!endLoop){
    if(line_loop.find(" ") != std::string::npos){
      line_columns.push_back(std::stof(line_loop.substr(0, line_loop.find(" "))));
      line_loop = line_loop.substr(line_loop.find(" ")+1);
    }else{
      line_columns.push_back(std::stof(line_loop));
      endLoop = true;
    }
  }

  //---------------------------
}
void PTS_importer::Loader_configuration(){
  //---------------------------

  switch(line_columns.size()){
    case 3 :{//XYZ
      config = 0;
      hasIntensity = false;
      hasNormal = false;
      hasColor = false;

      break;
    }
    case 4 :{//XYZ - I
      config = 1;
      hasIntensity = true;
      hasNormal = false;
      hasColor = false;

      break;
    }
    case 6 :{
      //XYZ - N
      if(abs(line_columns[3])<=1 && ((abs(line_columns[4])<=1 && abs(line_columns[5])<=1) || std::isnan(line_columns[4]))){
        config = 2;
        hasNormal = true;
        hasColor = false;
      }
      //XYZ - RGB
      if((abs(line_columns[3]) == 0 && abs(line_columns[4]) == 0 && abs(line_columns[5]) == 0) ||
      (abs(line_columns[3])>=1 && abs(line_columns[4])>=1 && abs(line_columns[5]>=1)) ){
        config = 3;
        hasColor = true;
        hasNormal = false;
        hasIntensity = false;
      }
      break;
    }
    case 7 :{
      //XYZ - I - RGB
      if((abs(line_columns[3]) == 0 && abs(line_columns[4]) == 0 && abs(line_columns[5]) == 0) ||
      (abs(line_columns[3])>=1 && abs(line_columns[4])>=1 && abs(line_columns[5]>=1) &&
      line_columns[6]>1) ){
        config = 4;
        hasColor = true;
        hasIntensity = true;
        hasNormal = false;
        break;
      }
      //XYZ - I - N
      if(abs(line_columns[4])<=1.1 && ((abs(line_columns[5])<=1.1 && abs(line_columns[6])<=1.1) || std::isnan(line_columns[5]))){
        config = 5;
        hasNormal = true;
        hasColor = false;
        hasIntensity = true;
        break;
      }
      //XYZ - RGB - I01
      if(line_columns[3]>=0 && line_columns[3]<=255 &&
       line_columns[4]>=0 && line_columns[4]<=255 &&
       line_columns[5]>=0 && line_columns[5]<=255 &&
       line_columns[6]>=0 && line_columns[6]<=1){
        config = 8;
        hasColor = true;
        hasIntensity = true;
        hasNormal = false;
        IdataFormat = 0;
        break;
      }
      break;
    }
    case 9 :{//XYZ - RGB - N
      config = 6;
      hasColor = true;
      hasNormal = true;
      hasIntensity = false;

      break;
    }
    case 10 :{
      //XYZ - RGB - N - I
      if(line_columns[3] >= 1 && line_columns[3] <= 255 && abs(line_columns[6]) >= 0 && abs(line_columns[6]) <= 1 ){
        config = 9;
        hasColor = true;
        hasIntensity = true;
        hasNormal = false;
        IdataFormat = 0;

        break;
      }

      //XYZ - I - RGB - N
      else{
        config = 7;
        hasColor = true;
        hasIntensity = true;
        hasNormal = true;

        if(line_columns[3]>=0 && line_columns[3]<=1){
          std::cout<<"I scale: [0;1]"<< std::endl;
          IdataFormat = 0;
        }
      }
      break;
    }
    default :{//XYZ - RGB
      config = 3;
      hasColor = true;
      hasNormal = false;
      hasIntensity = false;
    }
  }

  //----------------------------
  if(config == -1){
    std::cout<<"Failed to find file configuration ..."<< std::endl;
  }else{
    std::cout << "config " << config << std::flush;
  }

  //---------------------------
  endParameters = true;
}
void PTS_importer::Loader_data(Data_file* data, int FILE_config){
  std::istringstream iss(line);
  float x,y,z,r,g,b,I,nx,ny,nz;
  //---------------------------

  switch(FILE_config){
    case 0: iss >> x >> y >> z; break;
    case 1: iss >> x >> y >> z >> I; break;
    case 2: iss >> x >> y >> z >> nx >> ny >> nz; break;
    case 3: iss >> x >> y >> z >> r >> g >> b; break;
    case 4: iss >> x >> y >> z >> I >> r >> g >> b; break;
    case 5: iss >> x >> y >> z >> I >> nx >> ny >> nz; break;
    case 6: iss >> x >> y >> z >> r >> g >> b >> nx >> ny >> nz; break;
    case 7: iss >> x >> y >> z >> I >> r >> g >> b >> nx >> ny >> nz; break;
    case 8: iss >> x >> y >> z >> r >> g >> b >> I; break;
    case 9: iss >> x >> y >> z >> r >> g >> b >> I >> nx >> ny >> nz; break;
  }

  //Position data
  data->xyz.push_back(glm::vec3(x, y, z));

  //Reflectance data
  if(hasIntensity){
    if(IdataFormat == 0){
      data->Is.push_back(I);
    }else
    if(IdataFormat == 1){
      data->Is.push_back(I/255);
    }else
    if(IdataFormat == 2){
      data->Is.push_back((I+2048)/4096);
    }
  }

  //Normal data
  if(hasNormal){
    data->Nxyz.push_back(glm::vec3(nx, ny, nz));
  }

  //Color data
  if(hasColor){
    data->rgb.push_back(glm::vec4((r/255), (g/255), (b/255), 1.0f));
    //if reflectance value is coded in RGB format
    if(hasIntensity == false && r == g && g == b){
        data->Is.push_back(r/255);
        hasIntensity = true;
    }
  }

  //---------------------------
}

//Main exporter functions
bool PTS_importer::Exporter(std::string path, Object* object){
  //---------------------------

  //Create file
  if(path.substr(path.find_last_of(".") + 1) != "pts") path.append(".pts");
  std::ofstream file;
  file.open(path);
  if(!file){
    std::cout<<"Error in creating file !";
    return 0;
  }

  //Data : xyz (R) (rgb) (nxnynz)
  std::vector<glm::vec3>& XYZ = object->xyz;
  std::vector<glm::vec4>& RGB = object->rgb;
  std::vector<glm::vec3>& N = object->Nxyz;
  std::vector<float>& Is = object->Is;

  //Write in the file
  int precision = 6;
  file << XYZ.size() << std::endl;
  for(int i=0; i<XYZ.size(); i++){
    //Line start
    file << std::fixed;

    //Location
    file << std::setprecision(precision) << XYZ[i].x <<" "<< XYZ[i].y <<" "<< XYZ[i].z ;

    //Intensity
    if(object->Is.size() != 0){
      if(export_IdataFormat == 0){
        file << std::setprecision(precision) <<" "<< Is[i];
      }
      else if(export_IdataFormat == 1){
        file << std::setprecision(0) <<" "<< int(Is[i]*255);
      }
      else if(export_IdataFormat == 2){
        file << std::setprecision(0) <<" "<< int((Is[i]*4096)-2048);
      }
    }

    //Color
    if(object->has_color){
      file << std::setprecision(0) <<" "<< RGB[i].x * 255 <<" "<< RGB[i].y * 255 <<" "<< RGB[i].z * 255;
    }

    //Normal
    if(object->Nxyz.size() != 0){
      file << std::setprecision(precision) <<" "<< N[i].x <<" "<< N[i].y <<" "<< N[i].z;
    }

    //line end
    file << std::endl;
  }

  //---------------------------
  file.close();
  return true;
}

//Checking functions
bool PTS_importer::check_header(std::string path){
  std::string line;
  std::ifstream FILE(path);
  getline(FILE, line);
  //---------------------------

  //Column count
  std::vector<float> line_columns;
  bool endLoop = false;
  while(!endLoop){
    if(line.find(" ") != std::string::npos){
      line_columns.push_back(std::stof(line.substr(0, line.find(" "))));
      line = line.substr(line.find(" ")+1);
    }else{
      line_columns.push_back(std::stof(line));
      endLoop = true;
    }
  }

  //---------------------------
  if(line_columns.size() <= 1){
    return true;
  }
  return false;
}
int PTS_importer::check_configuration(std::string path){
  std::string line_loop;
  std::ifstream FILE(path);
  //---------------------------

  //pass the first line
  getline(FILE, line_loop);
  getline(FILE, line_loop);

  //Extraction of a line column
  bool endLoop = false;
  line_columns.clear();
  while(!endLoop){
    if(line_loop.find(" ") != std::string::npos){
      line_columns.push_back(std::stof(line_loop.substr(0, line_loop.find(" "))));
      line_loop = line_loop.substr(line_loop.find(" ")+1);
    }else{
      line_columns.push_back(std::stof(line_loop));
      endLoop = true;
    }
  }

  //Search file configuration
  switch(line_columns.size()){
    case 3 :{
      //XYZ
      config = 0;
      hasIntensity = false;
      hasNormal = false;
      hasColor = false;
      break;
    }
    case 4 :{
      //XYZ - I
      config = 1;
      hasIntensity = true;
      hasNormal = false;
      hasColor = false;
      break;
    }
    case 6 :{
      float R =line_columns[3];
      float G =line_columns[4];
      float B =line_columns[5];

      //XYZ - N
      bool color = abs(R) <= 1 && abs(G) <= 1 && abs(B) <= 1;
      bool nan = std::isnan(R) && std::isnan(G) && std::isnan(B);
      if(color || nan){
        config = 2;
        hasNormal = true;
        hasColor = false;
      }

      //XYZ - RGB
      bool empty = abs(R) == 0 && abs(G) == 0 && abs(B) == 0;
      bool normal = abs(R) >= 1 && abs(G) >= 1 && abs(B) >= 1;
      if(empty || normal){
        config = 3;
        hasColor = true;
        hasNormal = false;
        hasIntensity = false;
      }
      break;
    }
    case 7 :{
      float I =line_columns[3];
      float R =line_columns[4];
      float G =line_columns[5];
      float B =line_columns[6];

      //XYZ - I - RGB
      bool empty = abs(I) == 0 && abs(R) == 0 && abs(G) == 0 && abs(B) == 0;
      bool full = abs(I) >= 1 && abs(R) >= 1 && abs(G) >= 1 && abs(B) >= 1;
      if(empty || full){
        config = 4;
        hasColor = true;
        hasIntensity = true;
        hasNormal = false;
        break;
      }

      //XYZ - I - N
      bool normal = abs(R) <= 1.1f && abs(G) <= 1.1 && abs(B) <= 1.1;
      bool nan = std::isnan(R) && std::isnan(G) && std::isnan(B);
      if(normal || nan){
        config = 5;
        hasNormal = true;
        hasColor = false;
        hasIntensity = true;
        break;
      }

      //XYZ - RGB - I01
      bool a1 = I >= 0 && I <= 255;
      bool a2 = R >= 0 && R <= 255;
      bool a3 = G >= 0 && G <= 255;
      bool a4 = B >= 0 && B <= 1;
      if(a1 && a2 && a3 && a4){
        config = 8;
        hasColor = true;
        hasIntensity = true;
        hasNormal = false;
        IdataFormat = 0;
        break;
      }

      //XYZ - I01 - RBG
      bool b1 = I >= 0 && I <= 1;
      bool b2 = R >= 0 && R <= 255;
      bool b3 = G >= 0 && G <= 255;
      bool b4 = B >= 0 && B <= 255;
      if(b1 && b2 && b3 && b4){
        config = 4;
        hasColor = true;
        hasIntensity = true;
        hasNormal = false;
        IdataFormat = 0;
        break;
      }
      break;
    }
    case 9 :{
      //XYZ - RGB - N
      config = 6;
      hasColor = true;
      hasNormal = true;
      hasIntensity = false;
      break;
    }
    case 10 :{
      //XYZ - RGB - N - I[0;1]
      if(line_columns[3] >= 1 && line_columns[3] <= 255 && abs(line_columns[6]) >= 0 && abs(line_columns[6]) <= 1 ){
        config = 9;
        hasColor = true;
        hasIntensity = true;
        hasNormal = true;
        IdataFormat = 0;

        break;
      }
      //XYZ - RGB - N - I[-2048;+2047]
      else if(line_columns[3] >= 1 && line_columns[3] <= 255 && abs(line_columns[6]) > 1 && abs(line_columns[6]) <= 2048 ){
        config = 9;
        hasColor = true;
        hasIntensity = true;
        hasNormal = true;
        IdataFormat = 2;

        break;
      }
      else{//XYZ - I - RGB - N
        config = 7;
        hasColor = true;
        hasIntensity = true;
        hasNormal = true;

        float I =line_columns[3];
        bool Isc1 = abs(I) >= 0 && abs(I) <= 1;
        if(Isc1){
          IdataFormat = 0;
        }
      }
      break;
    }
    default :{//XYZ - RGB
      config = 3;
      hasColor = true;
      hasNormal = false;
      hasIntensity = false;
    }
  }

  //---------------------------
  if(config == -1){
    std::cout<<"Failed to find file configuration ..."<<" Nb columns: "<<line_columns.size()<< std::endl;
    std::cout << "config " << config << std::endl;
  }
  return config;
}
int PTS_importer::check_size(std::string path, bool FILE_hasHeader){
  //---------------------------

  int FILE_size = get_file_nbPoint(path);
  if(FILE_size > nbptMax){
    std::cout << "Too much points : "<< FILE_size << ">"<< nbptMax << std::endl;
  }
  if(FILE_hasHeader){
    FILE_size = FILE_size-1;
  }

  //---------------------------
  return FILE_size;
}
