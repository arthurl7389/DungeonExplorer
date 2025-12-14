#include "ThreadBackground.h"
#include "DungeonExplorer.h"
#include <sextant/interruptions/handler/handler_tic.h>

ThreadBackground::ThreadBackground(Semaphore *mut,DungeonExplorer* de){
	mutex = mut;
	DE = de;
};

void ThreadBackground::run(){
	// we use ticks to manage update frequency regardless of CPU speed
	const int TICKS_PER_SEC = 1000; // configured in main: timer.i8254_set_frequency(1000)
	const int UPS = 27; // updates per second desired
	const int TICKS_PER_UPDATE = TICKS_PER_SEC / UPS;

	int last = compt;
	int accumulator = 0;

	while (true) {
		int now = compt;
		int delta = now - last;
		if (delta < 0) delta = 0;
		accumulator += delta;
		last = now;

		while (accumulator >= TICKS_PER_UPDATE) { // we update game state at fixed intervals
			mutex->P(); // we lock the semaphore
			DE->backendCalculPosition(); // we update players and mobs positions
			mutex->V(); // we unlock the semaphore
			accumulator -= TICKS_PER_UPDATE;
		}

		thread_yield();
	}
};

char* ThreadBackground::getName() {
    return NAME;
}