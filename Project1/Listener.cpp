#include "Listener.h"



void Listener::on_external_callback(Event e) 
{
	// In real life, only the payload is passed here
	// Assembly of the Event(type , payload) happens here
	// but for demo, just pass Event here.
	//std::cout << "[Listener] got data :" << e.payload << "type "<< e.e_type <<std::endl;
	_q->enqueue(e);
}