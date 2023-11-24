#pragma once
#include "Event.h"
#include <thread>
#include <sstream>
#include <random>
#include "Listener.h"
#include <vector>

class Data_source
{
public:
	Data_source(Listener* l):L(l) { std::cout << "[External Source] test data sorce started"<<std::endl; }
	~Data_source() {
		_is_running = false;
		if (_th.joinable()) { _th.join(); }
	}

	void Start() 
	{
		_is_running = true;
		while (_is_running)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			Event res = this->gen_event();
			if (res.e_type > 0) 
			{
				L->on_external_callback(res);
			}
		}
	}

	Event gen_event() 
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		// Define the range for the random numbers
		std::uniform_int_distribution<> distrib(1, 100);

		// Generate a random number
		int randomNumber = distrib(gen);

		// Use stringstream to convert the number to a string
		std::stringstream ss;
		ss << randomNumber;
		std::string numberAsString = ss.str();
		Event e;
		if (dummy_ctr % 30 == 0) {
			e.e_type = _e_types[0];
		}
		else if (dummy_ctr % 5 == 0) {
			e.e_type = _e_types[2];
		}
		else if (dummy_ctr % 3 == 0) {
			e.e_type = _e_types[1];
		}
		else if (dummy_ctr % 100 == 0) {
			e.e_type = _e_types[3];
		}
		e.payload = numberAsString;
		dummy_ctr += 1;
		return e;
	}


private:
	std::thread _th;
	bool _is_running = false;
	Listener* L;
	std::vector<Eventtype> _e_types = { ontick_event,
										onorder_event,
										ontransac_event,
										low_freq_event };
	int dummy_ctr = 0;

};