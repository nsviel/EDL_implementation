#include "Path.h"

namespace fs = std::experimental::filesystem;


std::string get_path_abs_build(){
  //---------------------------

  fs::path currentPath = fs::current_path();
  std::string absPath = currentPath.string();
  absPath += "/";

  //---------------------------
  return absPath;
}
