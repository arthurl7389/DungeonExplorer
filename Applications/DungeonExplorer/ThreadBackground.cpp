#include "ThreadBackground.h"
#include "DungeonExplorer.h"

ThreadBackground::ThreadBackground(Semaphore *mut,DungeonExplorer* de){
	mutex = mut;
	DE = de;
};

void ThreadBackground::run(){
	while (true){
		mutex->P();

		DE->backendCalculPosition();

		mutex->V();
		thread_yield();
	}
};

char* ThreadBackground::getName() {
    return NAME;
}