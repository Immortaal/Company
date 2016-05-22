#pragma once
#include <mutex>
#include <deque>
#include <condition_variable>
#include <sstream>
#include <memory>
#include <string>

#include "Data.h"
using namespace std;

class Door
{
private:
	mutex mu;
	condition_variable freeDoor;
public:
	Door() {}
	void goThroughTheDoor(string who, unsigned id) {
		unique_lock<mutex> lock(mu);
		//freeDoor.wait(lock);
		stringstream s;
	//	cout <<who << " " << id << " przechodzi przez drzwi! Drzwi zajete!" << endl;
		//	Terminal::terminal().printForrest(s.str());
		lock.unlock();

		//freeDoor.notify_one();
	}
};
