#pragma once
#include <mutex>
#include <deque>
#include <condition_variable>
#include <sstream>
#include <memory>

#include "Data.h"
#include "Terminal.h"

using namespace std;

class Task
{
public:
	Task() : tasks(deque<int>(0,1)) {}

	void addTask() {
		unique_lock<mutex> lock(mu);
		not_full.wait(lock, [this]() {return tasks.size() < Data::getData().maxTasks; });
		tasks.push_front(1);
		lock.unlock();

		not_empty.notify_one();
		showState();
	}

	void getTask() {
		unique_lock<mutex> lock(mu);
		not_empty.wait(lock, [this]() {return tasks.size() > Data::getData().minTasks; });
		tasks.pop_back();
		lock.unlock();

		not_full.notify_one();
		showState();
	}

	void showState() {
		unique_lock<mutex> lock(mu);
		stringstream s;
		s << "Do wykonania zostalo:  " << tasks.size() << " zadan!" << endl;
		Terminal::terminal().printTasks(s.str());
		lock.unlock();

	}

private:
	deque<int> tasks;
	mutex mu;
	condition_variable not_empty;
	condition_variable not_full;

};
