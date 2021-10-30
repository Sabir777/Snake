#pragma once
#include <chrono>

using Time_point = std::chrono::time_point<std::chrono::steady_clock>;

class Timer {	
public:
	Timer();
	void set_time_point();
	int duration();
private:
	Time_point time_prev;
};