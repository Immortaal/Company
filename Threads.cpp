// Threads.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "Simulation.h"

/*
std::mutex mu;
std::mutex mu2;
std::condition_variable cond;
*/



// to avoid deadlock
// 1. prefer locking single mutex
// 2. avoid locking a mutex and then calling a user provided function
// 3. use std::lock() to lock more than one mutex
// 4. lock the mutex in same order for all threads




//std::lock(mu, mu2); // to avoid deadlock
// mutex is used for synchronizing
// never return resources
// never pass resources to other functions
/*

void shared_print(string msg) {
	std::unique_lock<mutex> locker2(mu2); // more flexible than lock quard
	cond.notify_one(); // notify one waiting thread if there is one
	// it should be in function where we produce sth
	cond.wait(locker2); // it should be in function where we want to get products
	//..dosth();
	locker2.unlock();
	std::lock_guard<std::mutex> guard(mu); // if cout throws exception, mu will be always closed
	mu.lock(); // only one thread can print sth
	cout << msg << endl;
	mu.unlock(); // we unlock resource so other threads can use it
}
void func()
{
	cout << "i'm thread!" << endl;
}
*/


// to avoid data race:
// use mutex to synchronize data access
// never leak a handle of data to outside
// design interface appropriately
/*

class stack {
	int* _data;
	std::mutex _mu;
public:
	void pop(); //pops off the item on top of the stack
	int& top(); // returns the item on top
	// pop and top should be one function if we dont want to have situation when
	// two threads call the pop function first so they get the same value

};

// deadlock - when you lock mutexes in two functions but in reverse order
// in one: mu then mu2
// in the second mu2 then mu
// to avoid this we should put mutexes in the same order in functions
void funcion(stack& st) {
	int v = st.top();
	st.pop();
}

*/


int main()
{
	//thread t1(func); // t1 starts running , create thread
	//t1.join(); // main thread waits for t1 to finish, close thread
	//t1.detach(); //t1 will freey on its own - deamon process

	Simulation s;
	s.run();
  return 0;
}

// deque - kolejka dwukierunkowa
//std::this_thread::sleep_for(chrono::seconds(1)); usypianie biezacego watku
