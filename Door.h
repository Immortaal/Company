#pragma once
#include <mutex>
#include <deque>
#include <condition_variable>
#include <sstream>
#include <memory>
#include <string>

#include "Data.h"
#include "Terminal.h"

using namespace std;

class Door
{
private:
	mutex mu;
	int busy;
	condition_variable freeDoor;
	condition_variable freeDoors;
public:
	Door() { this->busy = 1; }
	void goThroughTheDoor(string who, unsigned id) {
		unique_lock<mutex> lock(mu);
		freeDoor.wait(lock, [this]() {return this->busy == 1; });
		stringstream s;
		busy = 0;
		s <<who << " " << id << " przechodzi przez drzwi! Drzwi zajete!" << endl;
		Terminal::terminal().print("drzwi", s.str(), 0);
		lock.unlock();

		freeDoors.notify_one();
	}

	void goThroughDoor(string who, unsigned id) {
		unique_lock<mutex> lock(mu);
		freeDoors.wait(lock, [this]() {return this->busy == 0; });
		stringstream s;
		busy = 1;
		s <<who << " " << id << " przechodzi przez drzwi! Drzwi zajete!" << endl;
		Terminal::terminal().print("drzwi", s.str(), 0);
		lock.unlock();

		freeDoor.notify_one();
	}

};
