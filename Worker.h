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

class Worker
{
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
			s << "Pracownik " << id << " czeka by wykonac nowe zadanie."<<endl;
			Terminal::terminal().display("pracownicy", s.str(), id);
			t.getTask();
			logDoingTask();

			stringstream ss;
			ss << "Pracownik " << id << " czeka by umyc rece."<<endl;
			Terminal::terminal().display("pracownicy", ss.str(), id);
			b.takeToilet("Pracownik", this->id);
			logTakingToiletTime();

			stringstream sss;
			sss << "Pracownik " << id << " czeka by przejsc przez drzwi."<<endl;
			Terminal::terminal().display("pracownicy", sss.str(), id);
			d.goThroughDoor("Pracownik", this->id);
			logGoingThroughDoor();

		}
	}
	void logDoingTask() {
		unsigned parts = Data::getData().percent;
		unsigned addingTaskTime = Data::getData().doingTaskTime;
		stringstream s;
		s << "Pracownik " << id << " wykonuje zadanie";

		for (unsigned i = 1; i <= parts; i++) {
			Terminal::terminal().displayMove("pracownicy", s.str(), i*(100 / parts), id);
			this_thread::sleep_for(chrono::milliseconds(addingTaskTime / parts));

		}
	}
	void logTakingToiletTime() {
		unsigned parts = Data::getData().percent;
		unsigned takingToiletTime = Data::getData().takingToiletTime;
		stringstream s;
		s << "Pracownik " << id << " myje rece";

		for (unsigned i = 1; i <= parts; i++) {
			Terminal::terminal().displayMove("pracownicy", s.str(), i*(100 / parts), id);
			this_thread::sleep_for(chrono::milliseconds(takingToiletTime / parts));

		}
	}
	void logGoingThroughDoor() {
		unsigned parts = Data::getData().percent;
		unsigned goingThroughDoorTime = Data::getData().goingThroughTheDoorTime;
		stringstream s;
		s << "Pracownik " << id << " przechodzi przez drzwi";

		for (unsigned i = 1; i <= parts; i++) {
			Terminal::terminal().displayMove("pracownicy", s.str(), i*(100 / parts), id);
			this_thread::sleep_for(chrono::milliseconds(goingThroughDoorTime / parts));

		}
	}

public:
	Worker(unsigned id, Task& t, Bathroom& b, ParkingSpace& p, Door& d) : id(id), t(t), b(b), p(p), d(d), thread() {}
	~Worker() { thread.join(); }
	void start() {
		thread = std::thread(&Worker::work, this);
	}
};

using WorkerPtr = unique_ptr<Worker>;
// unique_ptr to wskaznik, ktory przechwouje na wylaczna wlasnosc obiekt poprzez wskaznik i usuwa ten obiekt, kiedy unique_ptr jest poza zakresem
// dwie instancje unique_ptr nie moga zarzadzac tym samym obiektem
