// C'est comme le producteur (Prod, cf. TP6)
#ifndef THREADBACKGROUND_H_
#define THREADBACKGROUND_H_

#include <sextant/Activite/Threads.h>
#include <sextant/Synchronisation/Semaphore/Semaphore.h>
#include <Applications/DungeonExplorer/DungeonExplorer.h>
/*
#include <drivers/Clavier.h>
#include <drivers/EcranBochs.h>
#include <sextant/sprite.h>
#include "Player.h"
#include "Mob.h"
*/


class ThreadBackground : public Threads {
	Semaphore *mutex;
	char* NAME = "Thread1";
    /*
    Clavier *clavier;
	EcranBochs *ecran;
	ui16_t WIDTH;
	ui16_t HEIGHT;
	const char SPEED = 1;
	Player *player1;
	Player *player2;
    int mobCount;
	Mob** mobs;
	*/
	DungeonExplorer *DE;
	
public:
	//ThreadBackground(Semaphore *mutex,EcranBochs*,Clavier*,ui16_t,ui16_t, Player*, Player*, int, Mob**);
	ThreadBackground(Semaphore *mutex,DungeonExplorer*);
	void run();
	void calculPosition();
	char* getName();
};
#endif