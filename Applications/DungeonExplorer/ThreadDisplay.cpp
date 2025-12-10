#include "ThreadDisplay.h"

//ThreadDisplay::ThreadDisplay(Semaphore *mut,EcranBochs* vga,Clavier* c,ui16_t w,ui16_t h,Player* p1,Player* p2,int mobcount,Mob** mobs_){
ThreadDisplay::ThreadDisplay(Semaphore *mut,DungeonExplorer* de){
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

void ThreadDisplay::run(){
	 mutex->P(); //prend le verrou, seulement lui peut travailler

	// do : affichage des infos (on peut pas les modifier si on est en train de les afficher, d'où le mutex)
	affichage();

	mutex->P(); //il a finit d'afficher, il rend le verrou
	thread_yield(); // on passe la main à un autre thread, pas obliger mais ça fait pas de mal
};

void ThreadDisplay::affichage(){
	/*
	TODO : finir ça, et réfléchir pour relancer le jeu à l'infinie, avec un truc pour lancer de nouvelles parties à chaque fois. 
	*/
}

char* ThreadDisplay::getName() {
    return NAME;
}