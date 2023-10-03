#include "Engine/Node.h"

#include <Window/Window_manager.h>
#include <iostream>
#include <stdexcept>


int main() {
  //---------------------------

  std::cout<<"--- \033[1;34mBegin program\033[0m ---"<<std::endl;
  try{
    Node node;
    Window_manager* window = new Window_manager();

    window->create_window(1024, 500, "Nephos"),
    node.init(window);
    node.loop();
    node.exit();

    delete window;
  }catch(const std::exception& e){
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  std::cout<<"--- \033[1;34mClose program\033[0m ---"<<std::endl;

  //---------------------------
  return EXIT_SUCCESS;
}
