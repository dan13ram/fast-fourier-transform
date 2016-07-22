#ifndef TIMER_H
#define TIMER_H
#include<chrono>
#include<ctime>

using namespace std::chrono;

class timer
{   
    duration<double,milliseconds::period> elapsed;
    steady_clock::time_point start;
    steady_clock::time_point end;    
    bool is_timer_started;
    bool is_timer_stopped;    
 public:
    timer():elapsed(0),is_timer_started(false),is_timer_stopped(false){}
    void start_timer();
    void stop_timer();
    void print_time_elapsed();    
};

#endif
