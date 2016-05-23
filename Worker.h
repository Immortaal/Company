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

		//	s << "Pracownik " << id << " czeka by odjechac z parkingu."<<endl;
		//	Terminal::terminal().print("pracownicy", s.str(), id);
		//	p.takeCar("Pracownik", this->id);
		//	logTakingCar();

		///	s << "Pracownik " << id << " czeka by zaparkowac auto."<<endl;
		//	Terminal::terminal().print("pracownicy", s.str(), id);
		//	p.parkCar("Pracownik", this->id);
		//	logParkingCar();

			s << "Pracownik " << id << " czeka by wykonac nowe zadanie."<<endl;
			Terminal::terminal().print("pracownicy", s.str(), id);
			t.getTask();
			logDoingTask();

stringstream ss;
			ss << "Pracownik " << id << " czeka by umyc rece."<<endl;
			Terminal::terminal().print("pracownicy", ss.str(), id);
			b.takeToilet("Pracownik", this->id);
			logTakingToiletTime();

stringstream sss;
			sss << "Pracownik " << id << " czeka by przejsc przez drzwi."<<endl;
			Terminal::terminal().print("pracownicy", sss.str(), id);
			d.goThroughDoor("Pracownik", this->id);
			logGoingThroughDoor();



		}
	}
	void logDoingTask() {
		unsigned parts = Data::getData().updateParts;
		unsigned addingTaskTime = Data::getData().doingTaskTime;
		stringstream s;
		s << "Pracownik " << id << " wykonuje zadanie";

		for (unsigned i = 1; i <= parts; i++) {
			Terminal::terminal().update("pracownicy", s.str(), i*(100 / parts), id);
			this_thread::sleep_for(chrono::milliseconds(addingTaskTime / parts));

		}
	}
	void logTakingToiletTime() {
		unsigned parts = Data::getData().updateParts;
		unsigned takingToiletTime = Data::getData().takingToiletTime;
		stringstream s;
		s << "Pracownik " << id << " myje rece";

		for (unsigned i = 1; i <= parts; i++) {
			Terminal::terminal().update("pracownicy", s.str(), i*(100 / parts), id);
			this_thread::sleep_for(chrono::milliseconds(takingToiletTime / parts));

		}
	}
	void logGoingThroughDoor() {
		unsigned parts = Data::getData().updateParts;
		unsigned goingThroughDoorTime = Data::getData().goingThroughTheDoorTime;
		stringstream s;
		s << "Pracownik " << id << " przechodzi przez drzwi";

		for (unsigned i = 1; i <= parts; i++) {
			Terminal::terminal().update("pracownicy", s.str(), i*(100 / parts), id);
			this_thread::sleep_for(chrono::milliseconds(goingThroughDoorTime / parts));

		}
	}
	void logParkingCar() {
		unsigned parts = Data::getData().updateParts;
		unsigned parkingCarTime = Data::getData().parkingCarTime;
		stringstream s;
	s << "Pracownik " << id << " parkuje auto";

		for (unsigned i = 1; i <= parts; i++) {
			Terminal::terminal().update("pracownicy", s.str(), i*(100 / parts), id);
			this_thread::sleep_for(chrono::milliseconds(parkingCarTime / parts));

		}
	}
	void logTakingCar() {
		unsigned parts = Data::getData().updateParts;
		unsigned takingCarTime = Data::getData().takingCarTime;
		stringstream s;
		s << "Pracownik " << id << " odjezdza z parkingu";

		for (unsigned i = 1; i <= parts; i++) {
			Terminal::terminal().update("pracownicy", s.str(), i*(100 / parts), id);
			this_thread::sleep_for(chrono::milliseconds(takingCarTime / parts));

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
