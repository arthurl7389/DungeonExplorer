// C'est comme le producteur (Prod, cf. TP6)

#ifndef THREADBACKGROUND_H_
#define THREADBACKGROUND_H_

#include <sextant/Activite/Threads.h>
#include <sextant/Synchronisation/Semaphore/Semaphore.h>


class ThreadBackground : public Threads {

	char *tableauProCons;
	Semaphore *sema;
	Ecran *ecran;
public:
	ThreadBackground(Semaphore *sem,char *tab,Ecran *ec);
	void run();
};

#endif