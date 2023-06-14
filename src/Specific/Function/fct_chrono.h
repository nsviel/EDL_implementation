#ifndef TICTOC_FUNCTIONS_H
#define TICTOC_FUNCTIONS_H

#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <list>


namespace{
  //---------------------------
  std::chrono::high_resolution_clock::time_point t1;

  //Time measurement
  auto timer_start(){
    auto start = std::chrono::high_resolution_clock::now();
  }
  template <typename Type> auto timer_stop(Type start){
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    return duration.count();
  }
  void tic(){
    t1 = std::chrono::high_resolution_clock::now();
  }
  void toc(std::string what){
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    float duration = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();
    std::cout<<what<<" time: "<<duration<<"ms"<<std::endl;
  }
  void toc_ms(std::string what){
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    float duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout<<what<<" time: "<<duration<<"ms"<<std::endl;
  }
  void toc_us(std::string what){
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    float duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout<<what<<" time: "<<duration<<"us"<<std::endl;
  }
  void toc_ns(std::string what){
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    float duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
    std::cout<<what<<" time: "<<duration<<"ns"<<std::endl;
  }
  float toc(){
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    float duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    //-------------
    return duration;
  }
  float toc_us(){
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    float duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    //-------------
    return duration;
  }
  float toc_ms(){
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    float duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    //-------------
    return duration;
  }
  float toc_s(){
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    float duration = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();

    //-------------
    return duration;
  }
  std::string epoch_to_utc(float epoch) {
    const std::time_t old = (std::time_t)epoch;
    struct tm *oldt = std::gmtime(&old);
    return std::asctime(oldt);
  }

  //---------------------------
}

#endif
