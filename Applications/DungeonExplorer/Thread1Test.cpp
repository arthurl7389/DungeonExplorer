#include "Thread1Test.h"

void Thread1Test::init(Mutex* mutex,EcranBochs* vga,Clavier* c,ui16_t w,ui16_t h,int* xpos,int* ypos){
	mutex = mutex;
    ecran=vga;
	clavier=c;
    WIDTH=w;
    HEIGHT=h;

    x = xpos;
    y = ypos;
};

void Thread1Test::run(){
	mutex->lock(); //prend le verrou : y'a que lui qui peut travailler

	// do : affichage des infos
    ecran->clear(1);
    ecran->plot_sprite(sprite_data_player1, SPRITE_WIDTH, SPRITE_HEIGHT, *x, *y);
	ecran->swapBuffer();
	

	mutex->unlock(); //il a finit d'afficher, il rend le verrou
};