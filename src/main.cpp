#include "Engine/Node.h"
#include "UI/UI_main.cpp"

#include <iostream>
#include <stdexcept>


int main() {
  Node node;
  //---------------------------

  std::cout<<"--- \033[1;34mBegin program\033[0m ---"<<std::endl;
  try{
    //run_gui_main();
    node.init();
    node.loop();
    node.exit();
  }catch(const std::exception& e){
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  std::cout<<"--- \033[1;34mClose program\033[0m ---"<<std::endl;

  //---------------------------
  return EXIT_SUCCESS;
}
