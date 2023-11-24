#include "Excutor.h"


void Excutor::init() 
{
	// bind the callback function of strategies or other moduels
	
	this->bind_Callback(ontick_event, &TaskBase::on_tick);
	this->bind_Callback(onorder_event, &TaskBase::on_order);
	this->bind_Callback(ontransac_event, &TaskBase::on_transac);
	this->bind_Callback(low_freq_event, &TaskBase::on_cus_event);
	
}

void Excutor::Start()
{
	std::unique_lock<std::mutex> lock(_mtx);
	if (_poolsize <= 0)
	{
		std::cout << " pool size cannot be 0" << std::endl;
		return;
	}
	if (!_tpool.empty() )
	{
		std::cout << " pool is has started or the pool is not empty" << std::endl;
		return;
	}

	_is_running = true;
	
	//Start pool first
	for (int i = 0; i < _poolsize; i++)
	{
		auto th = new std::thread(&Excutor::thread_main, this);
		_tpool.push_back(th);
	}
	//Start dispatcher later
	_th = std::thread(&Excutor::dispatch, this);
}

void Excutor::Stop()
{
	_is_running = false;
	if (_th.joinable())
	{
		_th.join();
	}
	_cv.notify_all();
	for ( auto& th : _tpool)
	{
		th->join();
	}
}

void Excutor::dispatch()
{
	while (_is_running)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		std::lock_guard<std::mutex> lock(_mtx);
		Event temp_event = _q.dequeue();
		//std::cout << "[Dispatch] temp_event id" << &temp_event;
		//std::cout << " payload," << temp_event.payload << " type : " << temp_event.e_type << std::endl;
		auto it = _cb_mapping.find(temp_event.e_type);
		if (it == _cb_mapping.end()) {
			// Handle the case where there is no callback for this event type
			std::cout << "No callback found for this event type, Your etype is : " << temp_event.e_type << std::endl;
			return;
		}

		for (Strategy* sPtr : _strategy_list)
		{
			Task new_task;
			new_task.s = sPtr;
			new_task._e = temp_event;
			new_task._cb_funcPtr = it->second;
			_task_q.push(std::move(new_task));
		}
		_cv.notify_one();
	}
}

void Excutor::thread_main()
{
	while (_is_running)
	{
		Task item;
		{
			std::unique_lock<std::mutex> lock(_mtx);
			_cv.wait(lock, [this] { return !_task_q.empty(); });
			item = std::move(_task_q.front());
			_task_q.pop();
		}
		// call the Strategy's instance method
		//std::cout << "[Excutor] trying to process event of type " << item._e.e_type << " and payload: " << item._e.payload;
		//std::cout<<"func is "<< item .s << std::endl;
		(item.s->*item._cb_funcPtr)(item._e);
		//std::cout << "One task finished " << std::endl;
	}
}


void Excutor::add_strategy(Strategy* s)
{
	_strategy_list.push_back(s);
	_poolsize += 1;
}


void Excutor::bind_Callback(Eventtype e_type, FuncPtr func)
{
	_cb_mapping[e_type] =func;
}

void Excutor::unbind_Callback(Eventtype e_type)
{
	auto it = _cb_mapping.find(e_type);
	if (it != _cb_mapping.end()) {
		_cb_mapping.erase(e_type);
	}
	else {
		// Handle the case where there is no callback for this event type
		std::cout << "No callback found for this event type, Your etype is: " << e_type << std::endl;
	}
}


ThreadSafeQueue<Event>* Excutor::getQPtr()
{
	return &_q;
}
