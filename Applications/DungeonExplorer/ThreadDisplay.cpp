#include "ThreadDisplay.h"

ThreadDisplay::ThreadDisplay(Mutex *mutex,EcranBochs* vga,Clavier* c,ui16_t w,ui16_t h,Player* p1,Player* p2,int mobcount,Mob** mobs_){
	//sema=sem;
	mutex = mutex;
	
    ecran=vga;
	clavier=c;
	WIDTH=w;
	HEIGHT=h;
	player1 = p1;
	player2 = p2;
    mobCount=mobcount;
	mobs = mobs_;

};

void ThreadDisplay::run(){
	mutex->lock(); //prend le verrou : y'a que lui qui peut travailler

	// do : affichage des infos (on peut pas les modifier si on est en train de les afficher, d'où le mutex)
	affichage();

	mutex->unlock(); //il a finit d'afficher, il rend le verrou
};

void ThreadDisplay::affichage(){

}