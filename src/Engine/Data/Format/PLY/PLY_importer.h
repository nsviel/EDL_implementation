#ifndef PLY_IMPORTER_H
#define PLY_IMPORTER_H

#include <Specific/Struct/struct_data_file.h>
#include <Specific/File/Info.h>
#include <Specific/Function/fct_math.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <stdint.h>
#include <cstdint>


class PLY_importer
{
public:
  //Constructor / Destructor
  PLY_importer();
  ~PLY_importer();

public:
  //Main functions
  Data_file* Loader(std::string path_file);

private:
  //Loader data
  void Loader_header(std::ifstream& file);
  void Loader_ascii(std::ifstream& file);
  void Loader_ascii_withface(std::ifstream& file);
  void Loader_bin_little_endian(std::ifstream& file);
  void Loader_bin_little_endian_withface(std::ifstream& file);
  void Loader_bin_big_endian(std::ifstream& file);
  void Loader_bin_big_endian_withface(std::ifstream& file);

  //Loader subfunctions
  float reverse_float(const float inFloat);
  int reverse_int(const int inInt);
  void reorder_by_timestamp();
  int get_id_property(std::string name);
  float get_float_from_binary(char* data, int& offset);
  float get_double_from_binary(char* block_data, int& offset);
  float get_int_from_binary(char* data, int& offset);
  float get_uint8_from_binary(char* block_data, int& offset);
  float get_uint16_from_binary(char* block_data, int& offset);
  float get_uint32_from_binary(char* block_data, int& offset);
  float get_uchar_from_binary(char* block_data, int& offset);

private:
  Data_file* data;

  //Parametrization
  std::vector<std::string> property_type;
  std::vector<std::string> property_name;
  std::vector<int> property_size;
  std::string format;
  bool is_timestamp;
  bool is_intensity;
  bool is_normal;
  bool is_color;
  int point_data_idx;
  int point_number;
  int face_number;
  int property_number;
  int header_size;
};

#endif
