#pragma once
#include "TaskBase.h"
#include "Event.h"
class Strategy : public TaskBase 
{
public:
	Strategy(int num) : id(num) {}

	void on_tick(Event e) 
	{
		std::cout << "[Strategy] "<< id <<" on_tick triggered, value: " << e.payload << std::endl;
	}

	void on_order(Event e) 
	{
		std::cout << "[Strategy] " << id <<" on_order triggered, value: " << e.payload << std::endl;
	}

	void on_transac(Event e) 
	{
		std::cout << "[Strategy] " << id <<" on_transac triggered, value: " << e.payload << std::endl;
	}

	void on_cus_event(Event e) 
	{
		std::cout << "[Strategy] " << id << " on_cus_event triggered, value: " << e.payload << std::endl;
	}


private:
	int id;

};