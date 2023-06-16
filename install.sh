#!/bin/bash

# Nephos engine installation
# For now, this script only support apt package manager from ubuntu. For other linux related OS, try the following commands:

#Centos
#sudo dnf install vulkan-tools vulkan-loader-devel mesa-vulkan-devel vulkan-validation-layers-devel
#sudo dnf install glfw-devel libXi-devel libXxf86vm-devel
#sudo dnf install glm-devel

#Arch linux 
#sudo pacman -S vulkan-devel
#sudo pacman -S glfw-wayland libxi libxxf86vm # glfw-x11 for X11 users
#sudo pacman -S glm

echo -ne "[\e[92m#\e[0m] Installation for ubuntu related OS..."

# Ubuntu
sudo apt install vulkan-tools libvulkan-dev vulkan-validationlayers-dev spirv-tools
sudo apt install libglfw3-dev libxxf86vm-dev libxi-dev
sudo apt install libglm-dev

# LunarG SDK
wget -qO- https://packages.lunarg.com/lunarg-signing-key-pub.asc | sudo tee /etc/apt/trusted.gpg.d/lunarg.asc
sudo wget -qO /etc/apt/sources.list.d/lunarg-vulkan-1.3.243-jammy.list https://packages.lunarg.com/vulkan/1.3.243/lunarg-vulkan-1.3.243-jammy.list
sudo apt update
sudo apt install vulkan-sdk

echo -ne "[\e[92m#\e[0m] Done"
