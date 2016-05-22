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

		//	s << "Manager " << id << " czeka by zaparkowac auto."<<endl;

		//	Terminal::terminal().print("menagerzy", s.str(), id);
		//	p.parkCar("Manager", this->id);
		//	logParkingCar();

			s << "Manager " << id << " czeka by zlecic nowe zadanie."<<endl;
			Terminal::terminal().print("menagerzy", s.str(), id);
			t.addTask();
			logAddingTask();

		//	cout << "Manager " << id << " czeka by skorzystac z toalety."<<endl;
			//Terminal::terminal().print("menagerzy", s.str(), id);
	//		b.takeToilet("Manager" , this->id);
		//	logTakingToilet();

		//	cout << "Manager " << id << " czeka by przejsc przez drzwi."<<endl;
			//Terminal::terminal().print("menagerzy", s.str(), id);
		//	d.goThroughTheDoor("Manager", this->id);
		//	logGoingThroughDoor();

		//	cout << "Manager " << id << " czeka by odjechac z parkingu."<<endl;
			//Terminal::terminal().print("menagerzy", s.str(), id);
		//	p.takeCar("Manager", this->id);
		//	logTakingCar();


		}
	}

	void logAddingTask() {
		unsigned parts = Data::getData().updateParts;
		unsigned addingTaskTime = Data::getData().addingTaskTime;
		stringstream s;
		s << "Manager " << id << " zleca nowe zadanie";

		for (unsigned i = 1; i <= parts; i++) {
			Terminal::terminal().update("managerzy", s.str(), i*(100 / parts), id);
			this_thread::sleep_for(chrono::milliseconds(addingTaskTime / parts));

		}
	}

	void logTakingToilet() {
		unsigned parts = Data::getData().updateParts;
		unsigned takingToiletTime = Data::getData().takingToiletTime;
		stringstream s;
	//	cout << "Manager " << id << " korzysta z toalety"<<endl;

		for (unsigned i = 1; i <= parts; i++) {
		//	Terminal::terminal().update("menagerzy", s.str(), i*(100 / parts), id);
			this_thread::sleep_for(chrono::milliseconds(takingToiletTime / parts));

		}
	}

	void logGoingThroughDoor() {
		unsigned parts = Data::getData().updateParts;
		unsigned goingThroughDoorTime = Data::getData().goingThroughDoorTime;
		stringstream s;
	//	cout << "Manager " << id << " przechodzi przez drzwi"<<endl;

		for (unsigned i = 1; i <= parts; i++) {
		//	Terminal::terminal().update("menagerzy", s.str(), i*(100 / parts), id);
			this_thread::sleep_for(chrono::milliseconds(goingThroughDoorTime / parts));

		}
	}

	void logParkingCar() {
		unsigned parts = Data::getData().updateParts;
		unsigned parkingCarTime = Data::getData().parkingCarTime;
		stringstream s;
	//	cout << "Manager " << id << " parkuje auto"<<endl;

		for (unsigned i = 1; i <= parts; i++) {
		//	Terminal::terminal().update("menagerzy", s.str(), i*(100 / parts), id);
			this_thread::sleep_for(chrono::milliseconds(parkingCarTime / parts));

		}
	}

	void logTakingCar() {
		unsigned parts = Data::getData().updateParts;
		unsigned takingCarTime = Data::getData().takingCarTime;
		stringstream s;
	//	cout << "Manager " << id << " odjezdza z parkingu"<<endl;

		for (unsigned i = 1; i <= parts; i++) {
		//	Terminal::terminal().update("menagerzy", s.str(), i*(100 / parts), id);
			this_thread::sleep_for(chrono::milliseconds(takingCarTime / parts));

		}
	}
};

using ManagerPtr = unique_ptr<Manager>;
// unique_ptr to wskaznik, ktory przechwouje na wylaczna wlasnosc obiekt poprzez wskaznik i usuwa ten obiekt, kiedy unique_ptr jest poza zakresem
// dwie instancje unique_ptr nie moga zarzadzac tym samym obiektem
