#!/bin/bash

../extern/spir/glslc ../src/Engine/Shader/glsl/$1.vert -o ../src/Engine/Shader/spir/$1.spv
../extern/spir/glslc ../src/Engine/Shader/glsl/$2.frag -o ../src/Engine/Shader/spir/$2.spv
