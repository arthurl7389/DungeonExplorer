#ifndef THREAD2TEST_H_
#define THREAD2TEST_H_

#include <sextant/Activite/Threads.h>
#include <sextant/Synchronisation/Mutex/Mutex.h>
#include <drivers/Clavier.h>
#include <drivers/EcranBochs.h>
#include <sextant/sprite.h>
#include "Player.h"
#include "Mob.h"


class Thread2Test : public Threads {
	Mutex *mutex;
    Clavier *clavier;
	EcranBochs *ecran;
    ui16_t WIDTH;
	ui16_t HEIGHT;
	const char SPEED = 1;
    // ressources partagées : x et y
    int *x;
    int *y;

public:
	void init(Mutex*,EcranBochs*,Clavier*,ui16_t,ui16_t,int*,int*);
	void run();
};
#endif