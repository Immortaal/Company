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

	const unsigned updateParts = 10;

	const unsigned managers = 5;
	const unsigned workers = 5;
	const unsigned bosses = 2;
	const unsigned secretaries = 2;
	const unsigned chairwomen = 2;


	const unsigned addingTaskTime = 800; //ms
	const unsigned doingTaskTime = 1000; //ms

	const unsigned cleaningTime = 800; //ms
	const unsigned takingToiletTime = 600; //ms

	const unsigned makingCoffeeTime = 1200; //ms
	const unsigned takingCoffeeTime = 1000; //ms

	const unsigned parkingCarTime = 3600; //ms
	const unsigned takingCarTime = 1000; //ms

	const unsigned goingThroughDoorTime = 2000; //ms
	const unsigned goingThroughTheDoorTime = 1600; //ms

	const unsigned maxTasks = 50;
	const unsigned minTasks = 0;

	const unsigned maxCoffees = 20;
	const unsigned minCoffees = 0;

	const unsigned parkingSpacesNumber = 10;
};
