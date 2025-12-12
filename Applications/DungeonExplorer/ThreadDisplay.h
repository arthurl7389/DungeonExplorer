// C'est comme le consommateur (Cons, cf. TP6)
#ifndef THREADDISPLAY_H_
#define THREADDISPLAY_H_

#include <sextant/Activite/Threads.h>
#include <sextant/Synchronisation/Semaphore/Semaphore.h>

class DungeonExplorer;


class ThreadDisplay : public Threads {
	Semaphore *mutex;
	DungeonExplorer *DE;
	char* NAME = "Thread2";
public:
	ThreadDisplay(Semaphore *mutex,DungeonExplorer*);
	void run();
	char* getName();
};
#endif