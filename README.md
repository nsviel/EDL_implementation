# Nephos
## Vulkan-Based Point Cloud Engine

![screenshot](https://github.com/nsviel/Nephos/assets/80487132/711383b1-af32-4600-a0b5-3b0114052698)

## Documentation

<details><summary>Characteristics</summary>

This engine is primarily destined for point cloud visualization, it does not display triangle or line topologies for loaded objects.

A particular work on point cloud visualization shader has been made in this engine with the integration of the EDL shader algorithm presented in the Ph.D. thesis of Christian BOUCHENY.

</details>

<details><summary>Installation</summary>
For now the engine is only supported for Linux OS and was tested on Ubuntu 22.04LTS.

To proceed with the installation, run the script file in the program directory
```
./install.sh
```

Then compile and run the executable
```
 mkdir build && cd build && cmake .. && make -j4 && ./executable
