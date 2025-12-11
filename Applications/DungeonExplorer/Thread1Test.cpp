#include "Thread1Test.h"

Thread1Test::Thread1Test(Semaphore* mut,EcranBochs* vga,Clavier* c,ui16_t w,ui16_t h,int* xpos,int* ypos){
	mutex=mut;
    ecran=vga;
	clavier=c;
    WIDTH=w;
    HEIGHT=h;

    x = xpos;
    y = ypos;

};

void Thread1Test::run(){
    while(true) {
        mutex->P();
    
        // do : affichage des infos
        ecran->clear(1);
        ecran->plot_sprite(sprite_data_player1, SPRITE_WIDTH, SPRITE_HEIGHT, *x, *y);
        ecran->swapBuffer();
        
    
        mutex->V();
        thread_yield();
    }
};


char* Thread1Test::getName() {
    return NAME;
}