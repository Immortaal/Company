#pragma once
#include <mutex>
#include <deque>
#include <condition_variable>
#include <sstream>
#include <memory>

#include "Data.h"
#include "Terminal.h"

using namespace std;

class Coffee
{
private:
	deque<int> coffees;
	mutex mu;
	condition_variable not_empty;
	condition_variable not_full;

public:
	Coffee() : coffees(deque<int>(0, 1)) {}
	void makeCoffee() {
		unique_lock<mutex> lock(mu);
		not_full.wait(lock, [this]() {return coffees.size() < Data::getData().maxCoffees; });
		coffees.push_front(1);
		lock.unlock();

		not_empty.notify_one();
		showState();
	}
	void takeCoffee() {
		unique_lock<mutex> lock(mu);
		not_empty.wait(lock, [this]() {return coffees.size() > Data::getData().minCoffees; });
		coffees.pop_back();
		lock.unlock();

		not_full.notify_one();
		showState();
	}
	void showState() {
		unique_lock<mutex> lock(mu);
		stringstream s;
		cout << "W kuchni zostalo:  " << coffees.size() << " kaw!";
		Terminal::terminal().print("kawa" , s.str(), 0);
		lock.unlock();
	}
};
