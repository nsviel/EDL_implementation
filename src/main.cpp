#include "Application/Loop.h"

#include <iostream>
#include <stdexcept>


int main() {
  Loop loop;
  //---------------------------

  std::cout<<"--- \033[1;34mBegin program\033[0m ---"<<std::endl;
  try{
    loop.run();
  }catch(const std::exception& e){
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  std::cout<<"--- \033[1;34mClose program\033[0m ---"<<std::endl;

  //---------------------------
  return EXIT_SUCCESS;
}
