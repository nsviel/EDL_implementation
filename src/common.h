#ifndef COMMON_H
#define COMMON_H

//Include
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <optional>
#include <cstdlib>
#include <stdint.h>
#include <set>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <string>
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
#include "Specific/Function/fct_terminal.h"
#include "Specific/Function/fct_math.h"
#include "Specific/Function/fct_chrono.h"

//Data
#include "Data/Struct/struct_object.h"
#include "Data/Struct/struct_cloud.h"
#include "Data/Struct/struct_set.h"
#include "Data/Struct/struct_data_file.h"
#include "Data/Struct/struct_glyph.h"
#include "Data/Struct/struct_mesh.h"

//GUI
#include "../extern/imgui/imgui.h"
#include "../extern/imgui/imgui_impl_glfw.h"
#include "../extern/imgui/imgui_impl_vulkan.h"


#endif
