#include "Thread2Test.h"

void Thread2Test::init(Mutex *mutex,EcranBochs* vga,Clavier* c,ui16_t w,ui16_t h,int* xpos,int* ypos){
	mutex = mutex;
    ecran=vga;
	clavier=c;
    WIDTH=w;
    HEIGHT=h;

    x = xpos;
    y = ypos;
};

void Thread2Test::run(){
	mutex->lock(); //prend le verrou : y'a que lui qui peut travailler

	// do : modification des coordonnées
    if (clavier->is_pressed(AZERTY::K_Z)) {
        y -= SPEED;
        if (y < 0) y += HEIGHT;
    }
    if (clavier->is_pressed(AZERTY::K_Q)) {
        x -= SPEED;
        if (x < 0) x += WIDTH;
    }
    /*
    if (clavier->is_pressed(AZERTY::K_S)) {
        y = (y + SPEED) % HEIGHT;
    }
    if (clavier->is_pressed(AZERTY::K_D)) {
        x = (x + SPEED) % WIDTH;
    }*/

	mutex->unlock(); //il a finit d'afficher, il rend le verrou
};