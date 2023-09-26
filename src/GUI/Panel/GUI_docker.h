#ifndef GUI_DOCKER_H
#define GUI_DOCKER_H

#include "../../common.h"

class Node_gui;


class GUI_docker
{
public:
  //Constructor / Destructor
  GUI_docker(Node_gui* node_gui);
  ~GUI_docker();

public:
  //Main functions
  void docker_space_main();

private:

};

#endif
