#ifndef UDP_PARSER_VLP16_H
#define UDP_PARSER_VLP16_H

// Server side implementation of UDP client-server model

#include <Specific/Struct/struct_data_file.h>
#include <Specific/Function/fct_math.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <chrono>


class Parser_VLP16
{
public:
  //Constructor / Destructor
  Parser_VLP16();
  ~Parser_VLP16();

public:
  //Main functions
  Data_file* parse_packet(std::vector<int> packet);

  //Subfunctions
  bool parse_header(std::vector<int>& packet_dec);
  void parse_vector(std::vector<int> packet);
  void parse_blocks();
  void parse_azimuth();
  void parse_coordinates();
  void parse_timestamp();

  //Final processing function
  void reorder_by_azimuth(Data_file* cloud);
  void supress_empty_data();

  //Subsubfunctions
  std::vector<float> calc_timing_offsets();
  void make_supressElements(std::vector<glm::vec3>& vec, std::vector<int> idx);
  void make_supressElements(std::vector<float>& vec, std::vector<int> idx);

private:
  std::vector<std::vector<int>> blocks;
  std::vector<glm::vec3> packet_xyz;
  std::vector<float> packet_R;
  std::vector<float> packet_I;
  std::vector<float> packet_A;
  std::vector<float> packet_t;

  int nb_laser;
  int nb_sequences;
  float packet_ts_us;
  bool supress_emptyElements;
};

#endif
