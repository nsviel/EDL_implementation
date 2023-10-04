#include "PTX_importer.h"


//Constructor / Destructor
PTX_importer::PTX_importer(){
  //---------------------------

  this->option_separateCloud = false;
  this->option_scannerAtOrigin = false;
  this->option_applyCloudTransfo = true;
  this->retrieve_I = true;
  this->retrieve_RGB = true;
  this->retrieve_N = true;
  this->IdataFormat = 0;

  //---------------------------
}
PTX_importer::~PTX_importer(){}

//Main functions
Data_file* PTX_importer::Loader(std::string path){
  list_ptxCloud = new std::list<PTXCloud*>;
  PTXCloud* cloud = new PTXCloud;
  //---------------------------

  data = new Data_file();
  data->name = get_name_from_path(path);
  data->path_file = path;

  //Open file
  std::ifstream infile(path);

  //Data loop
  PC_line = 0;
  std::string line;
  while (std::getline(infile, line)){
    std::istringstream iss(line);
    x = 0; y = 0; z = 0; I = 0; r = 0; g = 0; b = 0;
    iss >> x >> y >> z >> I >> r >> g >> b;

    //New header detected -> new cloud
    if(abs(y) == 0 && abs(z) == 0 && abs(I) == 0 && PC_line >= 10){
      if(option_separateCloud){
        break;
      }
      std::cout <<"New cloud - nb of lines : "<<PC_line<< std::endl;
      list_ptxCloud->push_back(cloud);
      cloud = new PTXCloud;
      PC_line = 0;
    }

    this->Loader_header(cloud);
    this->Loader_data(cloud);

    PC_line++;
  }
  list_ptxCloud->push_back(cloud);

  //Scanner at origin
  if(option_scannerAtOrigin){
    this->Loader_scannerAtOrigin();
  }

  //Apply transfomation
  if(option_applyCloudTransfo){
    this->Loader_cloudTransformation();
  }

  //Assemble all clouds
  this->Loader_assembling();

  //---------------------------
  data->nb_element = data->xyz.size();
  return data;
}
bool PTX_importer::Exporter(std::string path){
  //---------------------------

  //Create file
  std::string format = get_format_from_path(path);
  if(format != "ptx") path.append(".ptx");
  std::ofstream file;
  file.open(path);
  if(!file)
  {
    std::cout <<"Error in creating file !";
    return 0;
  }
  /*
  for(int i=0; i<list_collection->size(); i++)
  {
    //Select clouds one by one
    Collection* collection = &*std::next(list_collection->begin(),i);

    //----->HEADER
    //***********************************
    int nbRows = 3;
    if(collection->list_obj[0].I.size() != 0) nbRows++;
    if(collection->list_obj[0].has_color) nbRows++;
    if(collection->list_obj[0].N.size() != 0) nbRows++;
    //number of columns
    file << collection->list_obj[0].nb_point << endl;
    //number of rows
    file << nbRows << endl;
    //scanner registered position
    glm::vec3& ScanPos = collection->scanner.Position;
    file << ScanPos.x << " " << ScanPos.y << " " << ScanPos.z << endl;
    //scanner orientation
    file << 1 << " " << 0 << " " << 0 << endl;
    file << 0 << " " << 1 << " " << 0 << endl;
    file << 0 << " " << 0 << " " << 1 << endl;
    //transformation matrix
    glm::mat4& transMat = collection->list_obj[0].trans;
    glm::mat4& rotMat = collection->list_obj[0].rotat;
    mat4 finalMat = transpose(transMat * rotMat);
    file << setprecision(6) << finalMat[0][0] << " " << finalMat[0][1] << " " << finalMat[0][2] << " " << finalMat[0][3] << endl;
    file << setprecision(6) << finalMat[1][0] << " " << finalMat[1][1] << " " << finalMat[1][2] << " " << finalMat[1][3] << endl;
    file << setprecision(6) << finalMat[2][0] << " " << finalMat[2][1] << " " << finalMat[2][2] << " " << finalMat[2][3] << endl;
    file << setprecision(6) << finalMat[3][0] << " " << finalMat[3][1] << " " << finalMat[3][2] << " " << finalMat[3][3] << endl;
    //***********************************

    //----->DATA
    //-> Data : xyz (R) (rgb) (nxnynz)

    int precision = 6;

    //Write in the file
    file << pos.size() << std::endl;
    for(int i=0; i<pos.size(); i++)
    {
      file << fixed;
      //---> xyz
      file << setprecision(precision) << pos[i].x <<" "<< pos[i].y <<" "<< pos[i].z ;

      //---> R
      if(collection->list_obj[0].I.size() != 0)
        file << setprecision(0) <<" "<< ref[i];

      //---> rgb
      //Color only
      if(collection->list_obj[0].has_color)
        file << setprecision(0) <<" "<< col[i].x * 255 <<" "<< col[i].y * 255 <<" "<< col[i].z * 255;

      //---> nx ny nz
      if(collection->list_obj[0].N.size() != 0)
        file << setprecision(precision) <<" "<< nor[i].x <<" "<< nor[i].y <<" "<< nor[i].z;

      //We end the line
      file << endl;
    }
  }
  */

  //---------------------------
  file.close();
  return true;
}

//Subfunctions
void PTX_importer::Loader_header(PTXCloud* cloud){
  //---------------------------

  //Scanner registered position
  if(PC_line == 2){
    cloud->rootTrans.x = x;
    cloud->rootTrans.y = y;
    cloud->rootTrans.z = z;
  }
  //Scanner registered axis
  if(PC_line >= 3 && PC_line <= 5){
    cloud->rootRotat[PC_line-3].x = x;
    cloud->rootRotat[PC_line-3].y = y;
    cloud->rootRotat[PC_line-3].z = z;
  }
  //Transformation matrix
  if(PC_line >= 6 && PC_line <= 9){
    cloud->transfMat[PC_line-6].x = x;
    cloud->transfMat[PC_line-6].y = y;
    cloud->transfMat[PC_line-6].z = z;
    cloud->transfMat[PC_line-6].w = I;
  }

  //---------------------------
}
void PTX_importer::Loader_data(PTXCloud* cloud){
  //---------------------------

  if(PC_line > 9){
    if(abs(r) >= 0.0001){
      //Location
      cloud->location.push_back(glm::vec3(x, y, z));

      //Intensity
      if(retrieve_I){
        if(IdataFormat == 0){
          cloud->intensity.push_back(I);
        }else
        if(IdataFormat == 1){
          cloud->intensity.push_back(I/255);
        }else
        if(IdataFormat == 2){
          cloud->intensity.push_back((I+2048)/4096);
        }
      }

      //Color
      if(retrieve_RGB){
        cloud->color.push_back(glm::vec4(r/255, g/255, b/255, 1.0f));
      }
    }
  }

  //---------------------------
}
void PTX_importer::Loader_assembling(){
  //Assemble into an unique cloud
  //---------------------------

  for(int i=0; i<list_ptxCloud->size(); i++){
    PTXCloud* cloud = *std::next(list_ptxCloud->begin(),i);

    for(int j=0; j<cloud->location.size(); j++){
      data->xyz.push_back(cloud->location[j]);
      data->Is.push_back(cloud->intensity[j]);
      data->rgb.push_back(cloud->color[j]);
    }
  }
  //---------------------------
}
void PTX_importer::Loader_cloudTransformation(){
  std::cout <<"---> Apply ptx cloud transformation"<< std::endl;
  //---------------------------

  for(int i=0; i<list_ptxCloud->size(); i++){
    PTXCloud* cloud = *std::next(list_ptxCloud->begin(),i);
    std::vector<glm::vec3>& XYZ = cloud->location;
    glm::mat4& MatT = cloud->transfMat;

    if(option_notUseZValue){
      MatT[3][2] = 0;
    }

    for(int j=0; j<XYZ.size(); j++){
      glm::vec4 pos = glm::vec4(XYZ[j].x, XYZ[j].y, XYZ[j].z, 1.0) * transpose(MatT);
      XYZ[j] = glm::vec3(pos.x, pos.y, pos.z);
    }
  }

  //---------------------------
}
void PTX_importer::Loader_scannerAtOrigin(){
  std::cout <<"---> Set cloud origin at scanner position"<< std::endl;
  //---------------------------

  for(int i=0; i<list_ptxCloud->size(); i++){
    PTXCloud* cloud = *std::next(list_ptxCloud->begin(),i);

    std::vector<glm::vec3>& XYZ = cloud->location;
    glm::vec3& scanTranslation = cloud->rootTrans;
    glm::mat3& scanRotation = cloud->rootRotat;

    if(option_notUseZValue){
      scanTranslation.z = 0;
    }

    for(int j=0; j<XYZ.size(); j++){
      //Translation
      float x = XYZ[j].x + scanTranslation.x;
      float y = XYZ[j].y + scanTranslation.y;
      float z = XYZ[j].z + scanTranslation.z;
      XYZ[j] = glm::vec3(x, y, z);

      //Rotation
      XYZ[j] = XYZ[j] * scanRotation;
    }
  }

  //---------------------------
}

//Retrieve format info from path
std::string PTX_importer::get_format_from_path(std::string path){
  if(path != ""){
    std::string name_format = path.substr(path.find_last_of("/\\") + 1);
    return name_format.substr(name_format.find_last_of("."), std::string::npos);
  }else{
    return "";
  }
}
