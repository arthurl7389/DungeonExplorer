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
    Clavier *clavier;
	EcranBochs *ecran;
	ui16_t WIDTH;
	ui16_t HEIGHT;
	const char SPEED = 1;
	Player player1;
	Player player2;

	Semaphore *sema;
public:
	ThreadDisplay(Semaphore *sem,char *tab,Ecran *ec);
	void run();
};

/* a priori on aura besoin de pas beaucoup de mutex/semaphore. 
Il y aura besoin de regarder les section critique : si on veut écrire(changer les coordonnées),
on doit dire : ok je bloque le mutex, j'écris et je repasse la main.
Et idem si je veux afficher, stop je prends le mutex, je fais mon affichage et ensuite le reste peu faire ses modifs
*/

#endif