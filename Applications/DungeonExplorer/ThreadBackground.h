#ifndef THREADBACKGROUND_H_
#define THREADBACKGROUND_H_

#include <sextant/Activite/Threads.h>
#include <sextant/Synchronisation/Semaphore/Semaphore.h>

class DungeonExplorer;


class ThreadBackground : public Threads {
	Semaphore *mutex;
	DungeonExplorer *DE;
	char* NAME = "Thread1";	
public:
	ThreadBackground(Semaphore *mutex,DungeonExplorer*);
	void run();
	char* getName();
};
#endif