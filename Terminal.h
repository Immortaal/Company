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
public:
	static Terminal& terminal() {
        static Terminal instance;
        return instance;
    }
    Terminal(Terminal const&) = delete;
    void operator=(Terminal const&) = delete;

	//mvwprintw(Window* w, int y, int x, const char* c);
		void print(string win, string msg, int id) {
      //  WINDOW* w = window[win];
        unique_lock<mutex> lock(mu);
				  WINDOW* w = window[win];
        mvwprintw(w, id+1, 1, msg.c_str());
        draw_borders(w);
        wrefresh(w);
				lock.unlock();
    }

		void update(std::string win, std::string msg, int percent, int id) {
        WINDOW* w = window[win];
        std::unique_lock<std::mutex> lock(mu);
        int bar_len = w->_maxx - msg.length() - 4;
        std::string text = msg + " " +progress(percent, bar_len);
        mvwprintw(w, id+1, 1, text.c_str());
        draw_borders(w);
        wrefresh(w);
				lock.unlock();
    }

		void printTasks(std::string s) {
        std::unique_lock<std::mutex> lock(mu);
				WINDOW* w = window["zadania"];
				int xpos = w->_maxx/2 - s.length()/2;
        mvwprintw(w, 1, xpos, s.c_str());
        draw_borders(w);
        wrefresh(w);
    }


private:
	mutex mu;
	map<string, WINDOW*> window;


	Terminal() {
		initscr(); // init
    noecho(); // nie wyswietla wcisnietych klawiszy
    curs_set(FALSE); //widocznosc kursora = false

    int parent_x, parent_y;

/// stdscr oznacza okienko, konsole
/// getmaxyz zwraca nam rozmiary okna i zapisuje je do zmiennych
    getmaxyx(stdscr, parent_y, parent_x);

		// newwin(int nlines, int ncol, int begin_y, int begin_x)
		window["zadania"] = newwin(4, parent_x, 0,0);
		window["kawa"] = newwin(4, parent_x, 4, 0);
		window["miejsca parkingowe"] = newwin(3, parent_x, 8, 0);
		window["drzwi"] = newwin(3, parent_x/2, 11, 0);
		window["lazienka"] = newwin(3, parent_x/2, 11, parent_x/2);

		window["managerzy"] = newwin(7, parent_x, 14, 0);
		window["pracownicy"] = newwin(7, parent_x, 21, 0);
		window["szefowie"] = newwin(4, parent_x, 28, 0);
		window["sekretarki"] = newwin(4, parent_x, 32, 0);
		window["sprzataczki"] = newwin(4, parent_x, 36, 0);

		for( auto& elem : window) {
            draw_borders(elem.second);
            wrefresh(elem.second);
        }

	}
	~Terminal() {
		endwin(); // koniec rysowania w ncurses
	}

	void draw_borders(WINDOW *screen) {
	        int x, y, i;

	        getmaxyx(screen, y, x);

	//mvwprintw(Window* w, int y, int x, const char* c);
	        // 4 corners
	        mvwprintw(screen, 0, 0, "+");
	        mvwprintw(screen, y - 1, 0, "+");
	        mvwprintw(screen, 0, x - 1, "+");
	        mvwprintw(screen, y - 1, x - 1, "+");

	        // sides
	        for (i = 1; i < (y - 1); i++) {
	            mvwprintw(screen, i, 0, "|");
	            mvwprintw(screen, i, x - 1, "|");
	        }

	        // top and bottom
	        for (i = 1; i < (x - 1); i++) {
	            mvwprintw(screen, 0, i, "-");
	            mvwprintw(screen, y - 1, i, "-");
	        }
	    }

		std::string progress(int p, int parts) {
					float f_prog = (float)p/100.f * parts;
					int prog = std::ceil(f_prog);
					std::string s = "|";
					s.append(prog, '='); // prog razy wypisuje '='
					s.append(parts-prog, ' '); // tutaj wypisuje biale znaki
					s.append("|\n");
					return s;
	 }

};
