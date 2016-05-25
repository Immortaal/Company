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
	unsigned parkingSpaceNumber; // liczba wolnych miejsc parkingowych
public:
	ParkingSpace() { this->parkingSpaceNumber = 10; }

	void parkCar(string who, unsigned id) {
		unique_lock<mutex> lock(mu);
		freeParkingSpace.wait(lock, [this]() {return this->parkingSpaceNumber > 0; });
		stringstream s;
		--this->parkingSpaceNumber;
		s << who << " " << id << " zaparkowal swoj samochod! " << "Ilosc wolnych miejsc: " << this->parkingSpaceNumber;
		Terminal::terminal().displayState("miejscaparkingowe" , s.str() , this->parkingSpaceNumber, '#');
		lock.unlock();

		fullParkingSpace.notify_one();
	}
	void takeCar(string who, unsigned id) {
		unique_lock<mutex> lock(mu);
		fullParkingSpace.wait(lock, [this]() {return this->parkingSpaceNumber < 10; });
		stringstream s;
		++this->parkingSpaceNumber;
		s << who << " " << id << " odjechal z parkingu! " << "Ilosc wolnych miejsc: " << this->parkingSpaceNumber;
 		Terminal::terminal().displayState("miejscaparkingowe" , s.str() , this->parkingSpaceNumber, '#');
		lock.unlock();

		freeParkingSpace.notify_one();
	}
};
