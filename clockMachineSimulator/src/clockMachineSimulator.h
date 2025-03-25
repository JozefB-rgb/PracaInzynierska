#ifndef CLOCK_MACHINE_SIMULATOR_H

#define CLOCK_MACHINE_SIMULATOR_H

class clockMachineSimulator
{
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;

	long long uSec;

	int offsetYear;

	void updateTimeValues();

public:
	clockMachineSimulator();

	//function for testing constructor
	std::string getNoUpdatedTime();

	std::string getTime();
	int getYear();
	int getMonth();
	int getDay();
	int getHour();
	int getMin();
	int getSec();
	
	int getuSec();
};

#endif //CLOCK_MACHINE_SIMULATOR_H