#include "Core/Loop.h"
#include "UI/Vulkan/UI_main.h"

#include <iostream>
#include <stdexcept>


int main() {
  Loop loop;
  UI_main gui;
  //---------------------------

  //gui.run_gui_main();

  std::cout<<"--- \033[1;34mBegin program\033[0m ---"<<std::endl;
  try{
    loop.main_loop();
  }catch(const std::exception& e){
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  std::cout<<"--- \033[1;34mClose program\033[0m ---"<<std::endl;

  //---------------------------
  return EXIT_SUCCESS;
}
