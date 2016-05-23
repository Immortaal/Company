#pragma once
#include <thread>
#include <iostream>
#include <sstream>

#include "Coffee.h"
#include "ParkingSpace.h"
#include "Terminal.h"

using namespace std;

class Secretary
{
private:
	unsigned id;
	ParkingSpace& p;
	Coffee& c;
	std::thread thread;
	void work() {
		for (unsigned i = 0; ; i++) {
			stringstream s;

//			s << "Sekretarka " << id << " czeka by zaparkowac auto." << endl;
	///		Terminal::terminal().print("sekretarki", s.str(), id);
	//		p.parkCar("Sekretarka", this->id);
		//	logParkingCar();

			s << "Sekretarka " << id << " czeka by zrobic kawe." << endl;
			Terminal::terminal().print("sekretarki", s.str(), id);
			c.makeCoffee();
			logMakingCoffee();

stringstream ss;
			ss << "Sekretarka " << id << " czeka by odjechac z parkingu." << endl;
			Terminal::terminal().print("sekretarki", ss.str(), id);
			p.takeCar("Sekretarka", this->id);
			logTakingCar();
		}
	}
	void logMakingCoffee() {
		unsigned parts = Data::getData().updateParts;
		unsigned makingCoffeeTime = Data::getData().makingCoffeeTime;
		stringstream s;
		s << "Sekretarka " << id << " robi kawe";

		for (unsigned i = 1; i <= parts; i++) {
			Terminal::terminal().update("sekretarki", s.str(), i*(100 / parts), id);
			this_thread::sleep_for(chrono::milliseconds(makingCoffeeTime / parts));

		}
	}
	void logParkingCar() {
		unsigned parts = Data::getData().updateParts;
		unsigned parkingCarTime = Data::getData().parkingCarTime;
		stringstream s;
		s << "Sekretarka " << id << " parkuje auto";

		for (unsigned i = 1; i <= parts; i++) {
			Terminal::terminal().update("sekretarki", s.str(), i*(100 / parts), id);
			this_thread::sleep_for(chrono::milliseconds(parkingCarTime / parts));

		}
	}
	void logTakingCar() {
		unsigned parts = Data::getData().updateParts;
		unsigned takingCarTime = Data::getData().takingCarTime;
		stringstream s;
		s << "Sekretarka " << id << " odjezdza z parkingu";

		for (unsigned i = 1; i <= parts; i++) {
			Terminal::terminal().update("sekretarki", s.str(), i*(100 / parts), id);
			this_thread::sleep_for(chrono::milliseconds(takingCarTime / parts));

		}
	}
public:
	Secretary(unsigned id, ParkingSpace& p, Coffee& c ) : id(id), p(p), c(c),  thread() {}
	~Secretary() { thread.join(); }
	void start() {
		thread = std::thread(&Secretary::work, this);
	}
};

using SecretaryPtr = unique_ptr<Secretary>;
// unique_ptr to wskaznik, ktory przechwouje na wylaczna wlasnosc obiekt poprzez wskaznik i usuwa ten obiekt, kiedy unique_ptr jest poza zakresem
// dwie instancje unique_ptr nie moga zarzadzac tym samym obiektem
