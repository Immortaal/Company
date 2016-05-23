#pragma once
#include <thread>
#include <iostream>
#include <sstream>

#include "Coffee.h"
#include "Door.h"
#include "Terminal.h"

using namespace std;

class Boss
{
private:
	unsigned id;
	Door& d;
	Coffee& c;
	std::thread thread;
	void work() {
		for (unsigned i = 0; ; i++) {
			stringstream s;

			s << "Szef " << id << " czeka na kawe." << endl;
			Terminal::terminal().print("szefowie", s.str(), id);
			c.takeCoffee();
			logTakingCoffee();

stringstream ss;
			ss << "Szef " << id << " czeka by przejsc przez drzwi." << endl;
			Terminal::terminal().print("szefowie", ss.str(), id);
			d.goThroughTheDoor("Szef", this->id);
			logGoingThroughDoor();
		}
	}
	void logTakingCoffee() {
		unsigned parts = Data::getData().updateParts;
		unsigned takingCoffeeTime = Data::getData().takingCoffeeTime;
		stringstream s;
		s << "Szef " << id << " pije kawe";

		for (unsigned i = 1; i <= parts; i++) {
			Terminal::terminal().update("szefowie", s.str(), i*(100 / parts), id);
			this_thread::sleep_for(chrono::milliseconds(takingCoffeeTime / parts));

		}
	}
	void logGoingThroughDoor() {
		unsigned parts = Data::getData().updateParts;
		unsigned goingThroughDoorTime = Data::getData().goingThroughDoorTime;
		stringstream s;
		s << "Szef " << id << " przechodzi przez drzwi";

		for (unsigned i = 1; i <= parts; i++) {
			Terminal::terminal().update("szefowie", s.str(), i*(100 / parts), id);
			this_thread::sleep_for(chrono::milliseconds(goingThroughDoorTime / parts));

		}
	}
public:
	Boss(unsigned id, Door& d, Coffee& c) : id(id), d(d), c(c), thread() {}
	~Boss() { thread.join(); }
	void start() {
		thread = std::thread(&Boss::work, this);
	}
};

using BossPtr = unique_ptr<Boss>;
// unique_ptr to wskaznik, ktory przechwouje na wylaczna wlasnosc obiekt poprzez wskaznik i usuwa ten obiekt, kiedy unique_ptr jest poza zakresem
// dwie instancje unique_ptr nie moga zarzadzac tym samym obiektem
