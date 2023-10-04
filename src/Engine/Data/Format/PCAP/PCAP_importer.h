#ifndef PCAP_IMPORTER_H
#define PCAP_IMPORTER_H

#include <Specific/Struct/struct_data_file.h>
#include <Specific/File/Info.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <tins/tins.h>
#include <iostream>
#include <stddef.h>
#include <bitset>


class PCAP_importer
{
public:
  //Constructor / Destructor
  PCAP_importer();
  ~PCAP_importer();

public:
  Data_file* Loader(std::string pathFile);

  void Loader_vlp16(Data_file* data, std::string pathFile);
  void Loader_hdl32(Data_file* data, std::string pathFile);
  int get_file_length(std::string pathFile);

  inline void set_lidar_model(std::string value){this->LiDAR_model = value;}
  inline bool* get_packet_range_on(){return &packet_range_on;}
  inline int* get_packet_beg(){return &packet_beg;}
  inline int* get_packet_end(){return &packet_end;}

private:
  std::string LiDAR_model;
  bool packet_range_on;
  int packet_beg;
  int packet_end;
};

#endif
