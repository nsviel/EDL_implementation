#ifndef TIMER_H
#define TIMER_H

typedef decltype(std::chrono::high_resolution_clock::now()) timer_time;


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
  timer_time start_t(){
    auto t1 = std::chrono::high_resolution_clock::now();
    return t1;
  }
  float stop_s(timer_time t1){
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    return duration.count() / 1000.0f;
  }
  float stop_ms(timer_time t1){
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
    return duration.count() / 1000.0f;
  }
  float stop_us(timer_time t1){
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    return duration.count() / 1000.0f;
  }
  float stop_ns(timer_time t1){
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    return duration.count();
  }

private:
  std::chrono::high_resolution_clock::time_point t1;
  std::chrono::high_resolution_clock::time_point t2;
};

#endif
