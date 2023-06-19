#ifndef PCAP_IMPORTER_H
#define PCAP_IMPORTER_H

#include "../../../common.h"


class PCAP_importer
{
public:
  //Constructor / Destructor
  PCAP_importer();
  ~PCAP_importer();

public:
  vector<Data_file*> Loader(string pathFile);

  void Loader_vlp16(string pathFile);
  void Loader_hdl32(string pathFile);
  int get_file_length(string pathFile);

  inline void set_lidar_model(string value){this->LiDAR_model = value;}
  inline bool* get_packet_range_on(){return &packet_range_on;}
  inline int* get_packet_beg(){return &packet_beg;}
  inline int* get_packet_end(){return &packet_end;}

private:
  vector<Data_file*> data_vec;
  string LiDAR_model;
  bool packet_range_on;
  int packet_beg;
  int packet_end;
};

#endif
