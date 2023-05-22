#!/bin/bash

../extern/spir/glslc ../src/Engine/Shader/glsl/shader_scene_vs.vert -o ../src/Engine/Shader/spir/shader_scene_vs.spv
../extern/spir/glslc ../src/Engine/Shader/glsl/shader_scene_fs.frag -o ../src/Engine/Shader/spir/shader_scene_fs.spv
