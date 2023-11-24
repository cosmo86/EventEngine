#pragma once
#include <string>
#include <iostream>
enum Eventtype
{
	ontick_event,
	onorder_event,
	ontransac_event,
	low_freq_event
};

class Event
{
public:
	Event() {}
	Event(Eventtype e_type, std::string payload) :e_type(e_type), payload(payload) { std::cout << "[Event] event created" << std::endl; }
	~Event() {}


	// the following three methods are only used in ThreadSafeQueue class
	// enqueue() and dequeue() methods which are already thread-safe.
	// to avoid performance overhead, no need to locks here

	Eventtype e_type;
	std::string payload;
private:

};