#include "ThreadDisplay.h"
#include "DungeonExplorer.h"

ThreadDisplay::ThreadDisplay(Semaphore *mut,DungeonExplorer* de){
	mutex = mut; // semaphore for synchronization
	DE = de; // pointer to main DungeonExplorer object
};

void ThreadDisplay::run(){
	while (true) {
		mutex->P(); // we lock the semaphore

		if (DE->inGame()){
			DE->frontendAffichageInGame(); // if we are in game, we display the game frame
			mutex->V(); // we unlock the semaphore
			thread_yield();
		} else {
			DE->frontendAffichageEnd(); // if the game is finished, we display the end game screen
			if (DE->launchGame() != 0){ // we manage game restart (one or two players)
				DE->reset();
				if (DE->launchGame() == 1) {
				    DE->onePlayerMode();
				}
			}
			mutex->V(); // we unlock the semaphore
			thread_yield();
		}

	}
};

char* ThreadDisplay::getName() {
    return NAME;
}