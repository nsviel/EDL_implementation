#include "Node.h"

#include <iostream>
#include <stdexcept>


int main() {
  Node node;
  //---------------------------

  try{
    node.init();
    node.loop();
    node.exit();
  }catch(const std::exception& e){
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  //---------------------------
  return EXIT_SUCCESS;
}
