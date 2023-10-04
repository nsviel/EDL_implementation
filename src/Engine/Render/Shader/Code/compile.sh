#!/bin/bash

../extern/spir/glslc ../src/Engine/Render/Shader/Code/glsl/$1.vert -o ../src/Engine/Render/Shader/Code/spir/$1.spv
../extern/spir/glslc ../src/Engine/Render/Shader/Code/glsl/$2.frag -o ../src/Engine/Render/Shader/Code/spir/$2.spv
