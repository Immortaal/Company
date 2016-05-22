#pragma once
#include <thread>
#include <iostream>
#include <sstream>

#include "Bathroom.h"
#include "Data.h"

using namespace std;

class Charwoman
{
private:
	unsigned id;
	Bathroom& b;
	std::thread thread;
	void work() {
		for (unsigned i = 0; ; i++) {
			stringstream s;

			s << "Sprzataczka " << id << " czeka by posprzatac lazienke." << endl;
			//Terminal::terminal().print("forester", s.str(), id);
			b.cleanToilet("Sprzataczka", this->id);
			log();
		}
	}
	void log() {
		unsigned parts = Data::getData().updateParts;
		unsigned cleaningTime = Data::getData().cleaningTime;
		stringstream s;
		s << "Sprzataczka " << id << " sprzata lazienke" << endl;

		for (unsigned i = 1; i <= parts; i++) {
			//Terminal::terminal().update("forester", s.str(), i*(100 / parts), id);
			this_thread::sleep_for(chrono::milliseconds(cleaningTime / parts));

		}
	}
public:
	Charwoman(unsigned id, Bathroom& b) : id(id), b(b), thread() {}
	~Charwoman() { thread.join(); }
	void start() {
		thread = std::thread(&Charwoman::work, this);
	}
};

using CharwomanPtr = unique_ptr<Charwoman>;
// unique_ptr to wskaznik, ktory przechwouje na wylaczna wlasnosc obiekt poprzez wskaznik i usuwa ten obiekt, kiedy unique_ptr jest poza zakresem
// dwie instancje unique_ptr nie moga zarzadzac tym samym obiektem
