#ifndef CAPTURE_FRAME_H
#define CAPTURE_FRAME_H

#include <Specific/Struct/struct_data_file.h>
#include <Specific/Function/fct_math.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <chrono>


class Capture_frame
{
public:
  //Constructor / Destructor
  Capture_frame();
  ~Capture_frame();

public:
  //Main functions
  bool build_frame(Data_file* cloud);
  void reset_frame();

  //Subfunctions
  void add_cloudsToFrame(Data_file* cloud);
  void end_cloudsToFrame(Data_file* cloud, int index);

  inline Data_file* get_endedFrame(){return frame_ended;}

private:
  Data_file* frame_onrun;
  Data_file* frame_ended;
};

#endif
