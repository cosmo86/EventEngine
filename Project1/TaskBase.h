#pragma once
#include <thread>
#include <iostream>
#include "Event.h"

class TaskBase
{
public:
	TaskBase() = default;

	virtual void on_tick(Event e) {};
	virtual void on_order(Event e) {};
	virtual void on_transac(Event e) {};
	virtual void on_cus_event(Event e) {};

private:


};

