#pragma once
#include <iostream>
#include "ThreadSafeQueue.h"
#include "Event.h"
#include <thread>
#include <map>


class Listener
{
public:
	Listener(ThreadSafeQueue<Event>* q): _q(q) { std::cout << "[Listener] listener created"<<std::endl; }
	~Listener() { std::cout << "[Listener] listener destoried"<<std::endl; }


	virtual void on_external_callback(Event e);

private:
	ThreadSafeQueue<Event>* _q;


};

