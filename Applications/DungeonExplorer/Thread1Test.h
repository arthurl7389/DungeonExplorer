#ifndef THREAD1TEST_H_
#define THREAD1TEST_H_

#include <sextant/Activite/Threads.h>
#include <sextant/Synchronisation/Semaphore/Semaphore.h>
#include <drivers/Clavier.h>
#include <drivers/EcranBochs.h>
#include <sextant/sprite.h>
#include "Player.h"
#include "Mob.h"


class Thread1Test : public Threads {
	Semaphore *mutex;
    Clavier *clavier;
	EcranBochs *ecran;
    ui16_t WIDTH;
	ui16_t HEIGHT;
	const char SPEED = 1;
    int *x;
    int *y;
	char* NAME = "Thread1";
public:
	Thread1Test(Semaphore*,EcranBochs*,Clavier*,ui16_t,ui16_t,int*,int*);
	void run();
	char* getName();
};
#endif