#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string>
#include <vector>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <random>
#include <fstream>
#include <unistd.h>
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <experimental/filesystem>


//Directory operations
void dir_clean_file(const char *path);
void dir_create_new(std::string path);
int dir_number_file(std::string path);

//Check existence
bool is_file_exist(std::string fileName);
bool is_dir_exist(std::string path);
std::string is_dir_or_file(std::string path);

//List files & paths
std::vector<std::string> list_all_file(std::string path);
std::vector<std::string> list_all_path(std::string path);
std::vector<std::string> list_all_dir(std::string path);


#endif
