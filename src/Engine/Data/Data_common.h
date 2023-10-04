#ifndef COMMON_DATA_H
#define COMMON_DATA_H

//Include
#include <glm/glm.hpp>
#include <iostream>
#include <stdexcept>
#include <optional>
#include <cstdlib>
#include <stdint.h>
#include <set>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <iomanip>
#include <sys/file.h>
#include <chrono>
#include <array>
#include <vulkan/vulkan.h>
#include <thread>
#include <typeindex>
#include <any>
#include <utility>
#include <functional>

//Namespaces
using namespace std;
using namespace glm;

//Function
#include <Specific/Function/fct_terminal.h>
#include <Specific/Function/fct_math.h>
#include <Specific/Function/fct_chrono.h> //For debuging
#include <Specific/Function/fct_timer.h>  //For time profilling

//Data
#include <Specific/Struct/struct_object.h>
#include <Specific/Struct/struct_data_file.h>
#include <Specific/Struct/struct_set.h>
#include <Specific/Struct/struct_glyph.h>


#endif
