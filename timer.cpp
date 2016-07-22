#include"timer.h"
#include<chrono>
#include<iostream>
#include<ctime>

using namespace std::chrono;

void timer::start_timer()
{   
    if(!is_timer_started)
    {
        is_timer_started = true;
        is_timer_stopped = false;
        start = steady_clock::now();
    }
}

void timer::stop_timer()
{   
    if(is_timer_started && !is_timer_stopped )
    {
     is_timer_started = false;
     is_timer_stopped = true;
     end = steady_clock::now();     
     elapsed += end - start;
    }
}

void timer::print_time_elapsed()
{
    if(!is_timer_stopped)
        return;
    std::cout<<"wall clock time :"<<static_cast<double>(elapsed.count())<<"\n";  
}
