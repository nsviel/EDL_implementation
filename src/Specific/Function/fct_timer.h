/*
  COPYRIGHT © 2018 Ringo Hoffmann (zekro Development)
  READ BEFORE USING: https://zekro.de/policy
  https://gist.github.com/zekroTJA/00317b41aa69f38090071b6c8065272b

	Create asynchronous timers which execute specified functions in set time interval.
*/

#pragma once

#include <iostream>
#include <chrono>
#include <functional>
#include <thread>


class Timer
{
public:
	Timer(){}
	Timer(std::function<void(void)> func, const long &interval) {
		m_func = func;
		m_interval = interval;
	}
	~Timer(){
		stop();
	}

	//Main function
	void start(){
		//Starting the timer
		m_running = true;
		m_thread = std::thread([&]() {
			while (m_running) {
				auto delta = std::chrono::steady_clock::now() + std::chrono::milliseconds(m_interval);
				m_func();
				std::this_thread::sleep_until(delta);
			}
		});
		m_thread.detach();
	}
	void stop(){
		//Stopping the timer and destroys the thread.
		m_running = false;
		m_thread.~thread();
	}
	void restart(){
		//Restarts the timer. Needed if you set a new timer interval for example.
		stop();
		start();
	}
	
	//Accesseur
	long get_interval(){
		//Returns the current set interval in milliseconds.
		return m_interval;
	}
	bool get_is_running(){
		//Check if timer is running.
		return m_running;
	}
	Timer *set_func(std::function<void(void)> func){
		//Set the method of the timer after initializing the timer instance.
		m_func = func;
		return this;
	}
	Timer *set_interval(const long &interval){
		//Set a new interval for the timer in milliseconds.
		//This change will be valid only after restarting the timer.
		m_interval = interval;
		return this;
	}

private:
	long m_interval; // Timer interval in milliseconds
	bool m_running = false; // Status if timer is running
	std::function<void(void)> m_func; // Function to be executed fater interval
	std::thread m_thread; // Thread timer is running into
};
