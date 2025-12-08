#include "ThreadBackground.h"

ThreadBackground::ThreadBackground(Mutex *mutex,EcranBochs* vga,Clavier* c,ui16_t w,ui16_t h,Player* p1,Player* p2,int mobcount,Mob** mobs_){
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

void ThreadBackground::run(){
	mutex->lock(); //prend le verrou : y'a que lui qui peut travailler

	// do : calcul des positions (on peut pas les afficher si on est en train de les modifier, d'où le mutex)
	calculPosition();

	mutex->unlock(); //il a finit de changer les coordonnées, il rend le verrou
};

void calculPosition(){

}