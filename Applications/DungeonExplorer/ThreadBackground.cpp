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
		//thread_yield(); // on passe la main à un autre thread, pas obliger mais ça fait pas de mal
	}
};

char* ThreadBackground::getName() {
    return NAME;
}