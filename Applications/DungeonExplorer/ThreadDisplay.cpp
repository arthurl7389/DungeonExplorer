#include "ThreadDisplay.h"
#include "DungeonExplorer.h"

ThreadDisplay::ThreadDisplay(Semaphore *mut,DungeonExplorer* de){
	mutex = mut;
	DE = de;
};

void ThreadDisplay::run(){
	while (true) {
		mutex->P();

		if (DE->inGame()){
			DE->frontendAffichageInGame();
			mutex->V();
			thread_yield();
		} else {
			DE->frontendAffichageEnd();
			mutex->V();
			thread_yield();
		}

	}
};

char* ThreadDisplay::getName() {
    return NAME;
}