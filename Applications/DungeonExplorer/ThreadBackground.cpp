#include "ThreadBackground.h"

//ThreadBackground::ThreadBackground(Semaphore *mut,EcranBochs* vga,Clavier* c,ui16_t w,ui16_t h,Player* p1,Player* p2,int mobcount,Mob** mobs_){
ThreadBackground::ThreadBackground(Semaphore *mut,DungeonExplorer* de){
	mutex = mut;
	DE = de;
	/*
    ecran=vga;
	clavier=c;
	WIDTH=w;
	HEIGHT=h;
	player1 = p1;
	player2 = p2;
    mobCount=mobcount;
	mobs = mobs_;
	*/
};

void ThreadBackground::run(){
	 mutex->P(); //prend le verrou, seulement lui peut travailler

	// do : calcul des positions (on peut pas les afficher si on est en train de les modifier, d'où le mutex)
	calculPosition();

	 mutex->P(); //il a finit de changer les coordonnées, il rend le verrou
	 thread_yield(); // on passe la main à un autre thread, pas obliger mais ça fait pas de mal
};

void ThreadBackground::calculPosition(){

}

char* ThreadBackground::getName() {
    return NAME;
}