# Ubuntu
sudo apt install vulkan-tools libvulkan-dev vulkan-validationlayers-dev spirv-tools
sudo apt install libglfw3-dev libxxf86vm-dev libxi-dev
sudo apt install libglm-dev

#Centos
sudo dnf install vulkan-tools vulkan-loader-devel mesa-vulkan-devel vulkan-validation-layers-devel
sudo dnf install glfw-devel libXi-devel libXxf86vm-devel
sudo dnf install glm-devel

#Arch linux 
sudo pacman -S vulkan-devel
sudo pacman -S glfw-wayland libxi libxxf86vm # glfw-x11 for X11 users
sudo pacman -S glm

# Shader compiler
sudo cp glslc /usr/local/bin
