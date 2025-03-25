#ifndef CLOCK_MACHINE_SIMULATOR_H

#define CLOCK_MACHINE_SIMULATOR_H

class clockMachineSimulator
{
	//us per s
	int timeOffsetPerSecond;

	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;

	void updateTimeValues();

public:
	std::string getTime();
	int getYear();
	int getMonth();
	int getDay();
	int getHour();
	int getMin();
	int getSec();
};

#endif //CLOCK_MACHINE_SIMULATOR_H