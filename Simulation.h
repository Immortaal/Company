#pragma once
#include "Bathroom.h"
#include "Boss.h"
#include "Charwoman.h"
#include "Coffee.h"
#include "Data.h"
#include "Door.h"
#include "Manager.h"
#include "ParkingSpace.h"
#include "Secretary.h"
#include "Task.h"
#include "Worker.h"
#include "Terminal.h"

#include <vector>

class Simulation
{
private:
	Bathroom bathroom;
	Coffee coffee;
	Door door;
	ParkingSpace parkingSpace;
	Task task;

	vector<BossPtr> bosses;
	vector<CharwomanPtr> charwomen;
	vector<SecretaryPtr> secretaries;
	vector<ManagerPtr> managers;
	vector<WorkerPtr> workers;

	void init() {
	for (unsigned i = 0; i < 5; i++) {
		ManagerPtr manager { new Manager {i, task, bathroom, parkingSpace, door} };
		manager->start();
		managers.push_back(move(manager));
	}

	for (unsigned i = 0; i < 2; i++) {
		BossPtr boss { new Boss {i, door, coffee} };
		boss->start();
		bosses.push_back(move(boss));
	}

	for (unsigned i = 0; i < 2; i++) {
		CharwomanPtr charwoman{ new Charwoman {i, bathroom} };
		charwoman->start();
		charwomen.push_back(move(charwoman));
	}

	for (unsigned i = 0; i < 2; i++) {
		SecretaryPtr secretary { new Secretary {i, parkingSpace, coffee} };
		secretary->start();
		secretaries.push_back(move(secretary));
	}

	for (unsigned i = 0; i < 5; i++) {
		WorkerPtr worker{ new Worker {i, task, bathroom, parkingSpace, door} };
		worker->start();
		workers.push_back(move(worker));
	}
}
public:
	Simulation() : bathroom(), coffee(), door(), parkingSpace(), task() {}
	void run() { init(); }

};
