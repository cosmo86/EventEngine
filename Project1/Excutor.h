#pragma once
#include <iostream>
#include <thread>
#include <map>
#include <vector>
#include <list>
#include "ThreadSafeQueue.h"
#include "Event.h"
#include "TaskBase.h"
#include "Strategy.cpp"


struct Task
{
	typedef void (TaskBase::*FuncPtr)(const Event e);
	FuncPtr _cb_funcPtr;
	Event _e;
	Strategy* s;

};

class Excutor
{
public:
	typedef void (TaskBase::*FuncPtr)(const Event e);

	Excutor() { std::cout << "[Excutor] Excutor created"<<std::endl; }
	~Excutor() { std::cout << "[Excutor] Excutor destoried" << std::endl; }

	virtual void init();
	virtual void Start();
	virtual void Stop();
	virtual void bind_Callback(Eventtype e_type, FuncPtr func);
	virtual void unbind_Callback(Eventtype e_type);

	virtual void thread_main();
	virtual void add_strategy(Strategy* s);

	virtual void dispatch();
	virtual ThreadSafeQueue<Event>* getQPtr();
	
private:
	bool _is_running;
	std::thread _th;
	std::mutex _mtx;
	size_t _poolsize = 0;
	ThreadSafeQueue<Event>  _q;
	std::queue<Task>  _task_q;
	std::condition_variable _cv;
	std::map<Eventtype, FuncPtr > _cb_mapping;

	std::list<Strategy*>  _strategy_list;
	std::vector<std::thread*> _tpool;

};

