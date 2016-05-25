#pragma once
class Data
{
private:
	Data() {}

public:
	static Data& getData() {
		static Data data;
		return data;
	}
	Data(Data const&) = delete;
	void operator=(Data const&) = delete;

	const unsigned percent = 10;

	const unsigned addingTaskTime = 600;
	const unsigned doingTaskTime = 2800;

	const unsigned cleaningTime = 1000;
	const unsigned takingToiletTime = 800;

	const unsigned makingCoffeeTime = 800;
	const unsigned takingCoffeeTime = 1000;

	const unsigned parkingCarTime = 3600;
	const unsigned takingCarTime = 1000;

	const unsigned goingThroughDoorTime = 1000;
	const unsigned goingThroughTheDoorTime = 1000; 

};
