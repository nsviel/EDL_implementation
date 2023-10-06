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
#include <Specific/Struct/struct_set.h>
#include <Specific/Struct/struct_data_file.h>
#include <Specific/Struct/struct_glyph.h>

//GUI
#include <imgui/core/imgui.h>
#include <imgui/core/imgui_impl_glfw.h>
#include <imgui/core/imgui_internal.h>
#include <imgui/vulkan/imgui_impl_vulkan.h>


#endif
