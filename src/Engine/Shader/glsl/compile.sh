#!/bin/bash

../extern/glslc ../src/Engine/Shader/glsl/shader.vert -o ../src/Engine/Shader/spir/vert.spv
../extern/glslc ../src/Engine/Shader/glsl/shader.frag -o ../src/Engine/Shader/spir/frag.spv
