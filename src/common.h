#ifndef COMMON_H
#define COMMON_H

//Include
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <optional>
#include <cstdlib>
#include <stdint.h>
#include <set>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <string>
#include <iomanip>
#include <sys/file.h>
#include <chrono>
#include <array>
#include <vulkan/vulkan.h>

//Namespaces
using namespace std;
using namespace glm;

//Function
#include "Specific/Function/fct_terminal.h"
#include "Specific/Function/fct_math.h"

//Data
#include "Data/struct_cloud.h"
#include "Data/struct_set.h"
#include "Data/struct_data.h"


#endif
