# EventEngine
An c++ based multithreaded Event Engine with automating task-dispatching with thread-pool.

## Basic Usage
In Linux:not tested yet;
In windows: 
1. compile using Visual Studio 2017.
2. entry point is entry.cpp.

## More complex usage
1. you can modify the test data source content and delay between each data generation in test_data_source.h file.
2. you can create you own strategy by creating a cusStrategy.cpp file and inherit your strategy class from TaskBase.
3. you can even change the event type, now there are only 4 types of event, each correspons to a type of call_back function in strategy class. so when you change event type, make sure you create the related callback function.

