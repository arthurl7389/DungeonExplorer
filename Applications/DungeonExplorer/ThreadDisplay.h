// C'est comme le consommateur (Cons, cf. TP6)
#ifndef THREADDISPLAY_H_
#define THREADDISPLAY_H_

#include <sextant/Activite/Threads.h>
#include <sextant/Synchronisation/Semaphore/Semaphore.h>
#include <drivers/Clavier.h>
#include <drivers/EcranBochs.h>
#include <sextant/sprite.h>
#include "Player.h"
#include "Mob.h"


class ThreadDisplay : public Threads {
	Semaphore *mutex;
    
    Clavier *clavier;
	EcranBochs *ecran;
	ui16_t WIDTH;
	ui16_t HEIGHT;
	const char SPEED = 1;
	Player *player1;
	Player *player2;
    int mobCount;
	Mob** mobs;
	char* NAME = "Thread2";
public:
	ThreadDisplay(Semaphore *mutex,EcranBochs*,Clavier*,ui16_t,ui16_t, Player*, Player*, int, Mob**);
	void run();
	void affichage();
	char* getName();
};
#endif