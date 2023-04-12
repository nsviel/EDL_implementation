#include "Engine/Core/Engine.h"

#include <iostream>
#include <stdexcept>


int main() {
  Engine engine;
  //---------------------------

  try {
    engine.init_engine();
    engine.loop();
    engine.cleanup();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  //---------------------------
  return EXIT_SUCCESS;
}
