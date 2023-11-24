#include "test_data_source.h"
#include "Excutor.h"
#include "Strategy.cpp"

int main()
{
	Strategy S1(1);
	Strategy S2(2);
	Excutor excutor1;

	excutor1.add_strategy(&S1);
	excutor1.add_strategy(&S2);
	excutor1.init();
	excutor1.Start();

	Listener listener(excutor1.getQPtr());
	Data_source sender(&listener);
	sender.Start();


}