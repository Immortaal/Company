#pragma once
#include <thread>
#include <iostream>
#include <sstream>

#include "Task.h"
#include "Bathroom.h"
#include "Door.h"
#include "ParkingSpace.h"
#include "Terminal.h"

using namespace std;

class Manager
{
public:
	Manager(unsigned id, Task& t, Bathroom& b, ParkingSpace& p, Door& d) : id(id), t(t), b(b), p(p), d(d), thread() {}
	~Manager() { thread.join(); }

	void start() {
		thread = std::thread(&Manager::work, this);
	}
private:
	unsigned id;
	Task& t;
	Bathroom& b;
	ParkingSpace& p;
	Door& d;
	std::thread thread;

	void work() {
		for (unsigned i = 0; ; i++) {
			stringstream s;

			s << "Manager " << id << " czeka by zaparkowac auto."<<endl;
			Terminal::terminal().display("managerzy", s.str(), id);
			p.parkCar("Manager", this->id);
			logParkingCar();

			stringstream ss;
			ss << "Manager " << id << " czeka by zlecic nowe zadanie."<<endl;
			Terminal::terminal().display("managerzy", ss.str(), id);
			t.addTask();
			logAddingTask();
		}
	}

	void logAddingTask() {
		unsigned parts = Data::getData().percent;
		unsigned addingTaskTime = Data::getData().addingTaskTime;
		stringstream s;
		s << "Manager " << id << " zleca nowe zadanie";

		for (unsigned i = 1; i <= parts; i++) {
			Terminal::terminal().displayMove("managerzy", s.str(), i*(100 / parts), id);
			this_thread::sleep_for(chrono::milliseconds(addingTaskTime / parts));

		}
	}

	void logParkingCar() {
		unsigned parts = Data::getData().percent;
		unsigned parkingCarTime = Data::getData().parkingCarTime;
		stringstream s;
		s << "Manager " << id << " parkuje auto";

		for (unsigned i = 1; i <= parts; i++) {
		Terminal::terminal().displayMove("managerzy", s.str(), i*(100 / parts), id);
			this_thread::sleep_for(chrono::milliseconds(parkingCarTime / parts));

		}
	}
};

using ManagerPtr = unique_ptr<Manager>;
// unique_ptr to wskaznik, ktory przechwouje na wylaczna wlasnosc obiekt poprzez wskaznik i usuwa ten obiekt, kiedy unique_ptr jest poza zakresem
// dwie instancje unique_ptr nie moga zarzadzac tym samym obiektem
