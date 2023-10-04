#include "Format.h"
#include "../Format/PLY/PLY_importer.h"
#include "../Format/OBJ/OBJ_importer.h"
#include "../Format/CSV/CSV_importer.h"
#include "../Format/PCAP/PCAP_importer.h"
#include "../Format/PTS/PTS_importer.h"
#include "../Format/PTX/PTX_importer.h"
#include "../Format/XYZ/XYZ_importer.h"


//Constructor / Destructor
Format::Format(){
  //---------------------------

  this->ply_import = new PLY_importer();
  this->obj_import = new OBJ_importer();
  this->csv_import = new CSV_importer();
  this->pcap_import = new PCAP_importer();
  this->pts_import = new PTS_importer();
  this->ptx_import = new PTX_importer();
  this->xyz_import = new XYZ_importer();

  //---------------------------
}
Format::~Format(){
  //---------------------------

  delete ply_import;
  delete obj_import;
  delete csv_import;
  delete pcap_import;
  delete pts_import;
  delete ptx_import;
  delete xyz_import;

  //---------------------------
}

//Main functions
Data_file* Format::get_data_from_file(std::string path){
  Data_file* data;
  //---------------------------

  std::string format = get_format_from_path(path);
  if     (format == "ply"){
    data = ply_import->Loader(path);
  }
  else if(format == "obj"){
    data = obj_import->Loader(path);
  }
  else if(format == "csv"){
    data = csv_import->Loader(path);
  }
  else if(format == "pcap"){
    data = pcap_import->Loader(path);
  }
  else if(format == "pts"){
    data = pts_import->Loader(path);
  }
  else if(format == "ptx"){
    data = ptx_import->Loader(path);
  }
  else if(format == "xyz"){
    data = xyz_import->Loader(path);
  }

  //---------------------------
  return data;
}
