#ifndef TERMINAL_FUNCTIONS_H
#define TERMINAL_FUNCTIONS_H

#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <list>
#include <glm/glm.hpp>
#include <Eigen/Dense>


template<typename Type>
void say(Type truc);
void say(const glm::mat4 m);
void say(glm::vec2 truc);
void say(glm::vec3 truc);
void say(Eigen::Vector3d truc);
void say(std::vector<glm::vec2> truc);
void say(std::vector<glm::vec3> truc);
void say(std::vector<glm::vec4> truc);
void say(glm::vec4 truc);
template<typename Type>
void say(std::list<Type>& truc);

template<typename Type>
void saySize(Type truc);
template<typename Type>
void sayVec(std::vector<Type>& vec);

void sayMean(std::vector<glm::vec3> truc);
void sayHello();
void wtf();


#endif
