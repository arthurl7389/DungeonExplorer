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
		} else {
			DE->frontendAffichageEnd();
			mutex->V();
		}

	}
};

char* ThreadDisplay::getName() {
    return NAME;
}