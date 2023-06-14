#ifndef TIMELR_H
#define TIMELR_H


class Timer
{
public:
  //Constructor / Destructor
  Timer(){}
  ~Timer(){}

public:
  //Own timestamp
  void start(){
    this->t1 = std::chrono::high_resolution_clock::now();
  }
  float stop_s(){
    this->t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1);
    return duration.count();
  }
  float stop_ms(){
    this->t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    return duration.count();
  }
  float stop_us(){
    this->t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
    return duration.count();
  }
  float stop_ns(){
    this->t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    return duration.count();
  }

  //User declarative timestamp
  /*float start_s(){
    auto t1 = std::chrono::high_resolution_clock::now();
    return t1.count();
  }
  float stop_s(float t1){
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(t2);
    float elasped = duration.count() - t1;
    return elasped;
  }
  float stop_ms(float t1){
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2);
    float elasped = duration.count() - t1;
    return elasped;
  }
  float stop_us(float t1){
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2);
    float elasped = duration.count() - t1;
    return elasped;
  }
  float stop_ns(float t1){
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2);
    float elasped = duration.count() - t1;
    return elasped;
  }*/

private:
  std::chrono::high_resolution_clock::time_point t1;
  std::chrono::high_resolution_clock::time_point t2;
};

#endif
