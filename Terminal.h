#pragma once
#include <ncurses.h>
#include <mutex>
#include <cmath>
#include <map>
#include <string>

#include "Data.h"
using namespace std;

class Terminal
{
private:
	 mutex mu;
	 map<string, WINDOW*> window;

	 Terminal () {
	 	initscr(); // init
	 	noecho(); // nie wyswietla wcisnietych klawiszy
	 	curs_set(FALSE); //widocznosc kursora = false

	 	int parent_x, parent_y;

	 /// stdscr oznacza okienko, konsole
	 /// getmaxyz zwraca nam rozmiary okna i zapisuje je do zmiennych
	 	getmaxyx(stdscr, parent_y, parent_x);

	 	// newwin(int nlines, int ncol, int begin_y, int begin_x)
	 	window["zadania"] = newwin(4, parent_x, 0,0);
	 	window["kawa"] = newwin(3, parent_x, 4, 0);
	 	window["miejscaparkingowe"] = newwin(3, parent_x, 7, 0);
	 	window["drzwi"] = newwin(3, parent_x, 10, 0);
	 	window["lazienka"] = newwin(3, parent_x, 13, 0);

	 	window["managerzy"] = newwin(7, parent_x, 16, 0);
	 	window["pracownicy"] = newwin(7, parent_x, 23, 0);
	 	window["szefowie"] = newwin(4, parent_x, 30, 0);
	 	window["sekretarki"] = newwin(4, parent_x, 34, 0);
	 	window["sprzataczki"] = newwin(4, parent_x, 38, 0);

	 	for( auto& elem : window) {
	 					wrefresh(elem.second);
	 			}
	 }

	 ~Terminal() {
 		endwin(); // koniec rysowania w ncurses
 	}

		string showMove(int percent, int all) {
					float f = (float)percent * all /100.f;
					int move = ceil(f);
					string s = "";
					s.append(move, '>'); // move razy wypisuje '>'
					s.append("\n");
					return s;
				}

		string showState(int amount, char z) {
					string s = "";
					s.append(amount, z); // amount razy wypisuje dany znak
					s.append("\n");
					return s;
	 }

public:

	static Terminal& terminal() {
        static Terminal instance;
        return instance;
    }
    Terminal(Terminal const&) = delete;
    void operator=(Terminal const&) = delete;

	//mvwprintw(Window* w, int y, int x, const char* c);
		void display(string win, string msg, int id) {
        unique_lock<mutex> lock(mu);
				WINDOW* w = window[win];
				mvwprintw(w, id+1, 1, msg.c_str());
        wrefresh(w);
    }

		void displayMove(string win, string msg, int percent, int id) {
        unique_lock<mutex> lock(mu);
				WINDOW* w = window[win];
        int len = w->_maxx - msg.length() - 4;
        string text = msg + " " +showMove(percent, len);
        mvwprintw(w, id+1, 1, text.c_str());
        wrefresh(w);
    }

		void displayState(string win, string msg, int percent, char z) {
        unique_lock<mutex> lock(mu);
				WINDOW* w = window[win];
        string text = msg + " " +showState(percent, z);
        mvwprintw(w, 1, 1, text.c_str());
        wrefresh(w);
    }
};
