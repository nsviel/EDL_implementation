#include "PCAP_importer.h"

#include "Parser/Parser_VLP16.h"
#include "Parser/Parser_HDL32.h"
#include "Parser/Capture_frame.h"


using namespace Tins;
std::vector<std::vector<int>> file_packets;
size_t lenght(0);
int loop_beg(0);
int loop_end(0);
int loop_cpt(0);


//Constructor / Destructor
PCAP_importer::PCAP_importer(){
  //---------------------------

  this->LiDAR_model = "vlp16";
  this->packet_range_on = false;
  this->packet_beg = 0;
  this->packet_end = 0;

  //---------------------------
}
PCAP_importer::~PCAP_importer(){}

//PCAP reader callback
bool parse_packets(const PDU& packet){
  //---------------------------

  if(loop_cpt >= loop_beg && loop_cpt < loop_end){
    //Retrieve data packet
    const RawPDU raw = packet.rfind_pdu<RawPDU>();
    std::vector<uint8_t> buffer = raw.payload();

    //Convert into decimal vector
    std::vector<int> packet_dec;
    for(int i =0; i < buffer.size(); i++){
      std::bitset<8> octet(buffer[i]);

      int octet_32 = octet.to_ulong();
      packet_dec.push_back(octet_32);
    }

    //Store the packet
    file_packets.push_back(packet_dec);
  }

  loop_cpt++;

  //---------------------------
  return true;
}
bool count_packets(const PDU &){
    lenght++;
    return true;
}

//Main function
Data_file* PCAP_importer::Loader(std::string path){
  file_packets.clear();
  //---------------------------

  Data_file* data = new Data_file();
  data->name = get_name_from_path(path);
  data->path_file = path;

  //Set up parameters
  loop_cpt = 0;
  if(packet_range_on){
    loop_beg = packet_beg;
    loop_end = packet_end;
  }else{
    loop_beg = 0;
    loop_end = get_file_length(path);
  }

  //Check if vlp16 or hdl32
  if (path.find("HDL32") != std::string::npos){
    this->LiDAR_model = "hdl32";
  }else{
    this->LiDAR_model = "vlp16";
  }

  //Sniff UDP packets
  FileSniffer sniffer(path);
  sniffer.sniff_loop(parse_packets);

  //Parse data
  if(LiDAR_model == "vlp16"){
    this->Loader_vlp16(data, path);
  }
  else if(LiDAR_model == "hdl32"){
    this->Loader_hdl32(data, path);
  }

  //---------------------------
  return data;
}

void PCAP_importer::Loader_vlp16(Data_file* data, std::string path){
  Capture_frame frameManager;
  Parser_VLP16 udpManager;
  //---------------------------

  int cpt = 0;
  for(int i=0; i<file_packets.size(); i++){

    Data_file* cloud = udpManager.parse_packet(file_packets[i]);
    bool frame_rev = frameManager.build_frame(cloud);

    if(frame_rev){
      Data_file* frame = frameManager.get_endedFrame();
      Data_file* frame_data = new Data_file();

      frame_data->name = "frame_" + std::to_string(cpt); cpt++;
      frame_data->path_file = path;
      frame_data->nb_element = frame->xyz.size();

      for(int j=0; j<frame->xyz.size(); j++){
        frame_data->xyz.push_back(frame->xyz[j]);
        frame_data->Is.push_back(frame->Is[j]);
        frame_data->ts.push_back(frame->ts[j]);
        frame_data->A.push_back(frame->A[j]);
        frame_data->R.push_back(frame->R[j]);
      }

      data->vec_data.push_back(frame_data);
    }
  }

  //---------------------------
}
void PCAP_importer::Loader_hdl32(Data_file* data, std::string path){
  Capture_frame frameManager;
  Parser_HDL32 udpManager;
  //---------------------------

  for(int i=0; i<file_packets.size(); i++){
    Data_file* cloud = udpManager.parse_packet(file_packets[i]);
    bool frame_rev = frameManager.build_frame(cloud);

    if(frame_rev){
      Data_file* frame = frameManager.get_endedFrame();
      Data_file* frame_data = new Data_file();

      frame_data->path_file = path;
      frame_data->nb_element = frame->xyz.size();

      for(int j=0; j<frame->xyz.size(); j++){
        frame_data->xyz.push_back(frame->xyz[j]);
        frame_data->Is.push_back(frame->Is[j] / 255);
        frame_data->ts.push_back(frame->ts[j]);
        frame_data->A.push_back(frame->A[j]);
        frame_data->R.push_back(frame->R[j]);
      }

      data->vec_data.push_back(frame_data);
    }
  }

  //---------------------------
}
int PCAP_importer::get_file_length(std::string path){
  lenght = 0;
  //---------------------------

  FileSniffer sniffer(path);
  sniffer.sniff_loop(count_packets);

  //---------------------------
  return lenght;
}
