#include "Engine/Engine.h"

#include <Window/Window_manager.h>
#include <iostream>
#include <stdexcept>


int main() {
  //---------------------------

  std::cout<<"--- \033[1;34mBegin program\033[0m ---"<<std::endl;
  try{
    Engine engine;
    Window_manager* window = new Window_manager();

    window->create_window(1024, 500, "Nephos"),
    engine.init(window);
    engine.loop();
    engine.exit();

    delete window;
  }catch(const std::exception& e){
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  std::cout<<"--- \033[1;34mClose program\033[0m ---"<<std::endl;

  //---------------------------
  return EXIT_SUCCESS;
}
