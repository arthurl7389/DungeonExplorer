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
			if (DE->launchGame() != 0){
				DE->reset();
				if (DE->launchGame() == 1) {
				    DE->onePlayerMode();
				}
			}
			mutex->V();
			thread_yield();
		}

	}
};

char* ThreadDisplay::getName() {
    return NAME;
}