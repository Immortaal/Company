#pragma once
#include <mutex>
#include <deque>
#include <condition_variable>
#include <sstream>
#include <memory>

#include "Data.h"

using namespace std;

class ParkingSpace
{
private:
	mutex mu;
	condition_variable freeParkingSpace;
	condition_variable fullParkingSpace;
	unsigned parkingSpaceNumber;
public:
	ParkingSpace() { this->parkingSpaceNumber = Data::getData().parkingSpacesNumber; }
	void parkCar(string who, unsigned id) {
		unique_lock<mutex> lock(mu);
		freeParkingSpace.wait(lock, [this]() {return this->parkingSpaceNumber > 0; });
		stringstream s;
	//	cout << who << " " << id << " zaparkowal swoj samochod!" << endl;
		--this->parkingSpaceNumber;
		//	Terminal::terminal().printForrest(s.str());
		lock.unlock();

		fullParkingSpace.notify_one();
	}
	void takeCar(string who, unsigned id) {
		unique_lock<mutex> lock(mu);
		fullParkingSpace.wait(lock, [this]() {return this->parkingSpaceNumber < Data::getData().parkingSpacesNumber; });
		stringstream s;
	//	cout << who << " " << id << " odjechal z parkingu!" << endl;
		++this->parkingSpaceNumber;
		//	Terminal::terminal().printForrest(s.str());
		lock.unlock();

		freeParkingSpace.notify_one();
	}
	void showState() {
		unique_lock<mutex> lock(mu);
		stringstream s;
		//cout << "Zostalo:  " << this->parkingSpaceNumber << " wolnych miejsc parkingowych!" << endl;
		//	Terminal::terminal().printForrest(s.str());
		lock.unlock();
	}
};
