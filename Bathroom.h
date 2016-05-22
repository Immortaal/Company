#pragma once
#include <mutex>
#include <deque>
#include <condition_variable>
#include <sstream>
#include <memory>

using namespace std;

class Bathroom
{
private:
	mutex mu;
	int busy;
	condition_variable freeToilet;
	condition_variable freeClean;
public:
	Bathroom() { this->busy = 0; }
	void cleanToilet(string who, unsigned id) {
		unique_lock<mutex> lock(mu);
		freeClean.wait(lock, [this]() {return this->busy == 0; });
		stringstream s;
		busy = 1;
	//	cout << who << " " << id << " sprzata lazienke! Lazienka zajeta!" << endl;
		//	Terminal::terminal().printForrest(s.str());
		lock.unlock();

		freeToilet.notify_one();
	}
	void takeToilet(string who, unsigned id) {
		unique_lock<mutex> lock(mu);
		freeToilet.wait(lock, [this]() {return this->busy == 1; });
		stringstream s;
		busy = 0;
	//	cout << who << " " << id << " korzysta z lazienki! Lazienka zajeta!" << endl;
		//	Terminal::terminal().printForrest(s.str());
		lock.unlock();

		freeClean.notify_one();
	}
};
