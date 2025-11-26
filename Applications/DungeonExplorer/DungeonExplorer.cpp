#include "DungeonExplorer.h"
#include <drivers/EcranBochs.h>
#include <sextant/sprite.h>

void DungeonExplorer::init(EcranBochs* vga,Clavier* c,ui16_t WIDTH,ui16_t HEIGHT) {
	ecran=vga;
	clavier=c;
	WIDTH=WIDTH;
	HEIGHT=HEIGHT;
}

// 1 : un thread par mov joueur, un pour l'affichage du monde
// 2 : on modifie le monde dynamiquement, localement
// commence simple, après rend les choses plus compliqué, 
void DungeonExplorer::start() {
    while (true) {
		int x = 0, y = 0;
		int x2 = 100, y2 = 0;

		player1_action(x,y);
		player2_action(x2,y2);
		ecran->clear(1);
		ecran->plot_sprite(sprite_data_player1, SPRITE_WIDTH, SPRITE_HEIGHT, x, y);
		ecran->plot_sprite(sprite_data_player2, SPRITE_WIDTH, SPRITE_HEIGHT, x2, y2);
		ecran->plot_sprite(sprite_data_skeleton, SPRITE_WIDTH, SPRITE_HEIGHT, 300, 200);
		ecran->swapBuffer();
	}
}

void DungeonExplorer::player1_action(int x, int y){

        if (clavier->is_pressed(AZERTY::K_Z)) {
            y -= SPEED;
            if (y < 0) y += HEIGHT;
        }
        if (clavier->is_pressed(AZERTY::K_Q)) {
            x -= SPEED;
            if (x < 0) x += WIDTH;
        }
        if (clavier->is_pressed(AZERTY::K_S)) {
            y = (y + SPEED) % HEIGHT;
        }
        if (clavier->is_pressed(AZERTY::K_D)) {
            x = (x + SPEED) % WIDTH;
        }
	
}

void DungeonExplorer::player2_action(int x2, int y2){

		if (clavier->is_pressed(AZERTY::K_O)) {
            y2 -= SPEED;
            if (y2 < 0) y2 += HEIGHT;
        }
        if (clavier->is_pressed(AZERTY::K_K)) {
            x2 -= SPEED;
            if (x2 < 0) x2 += WIDTH;
        }
        if (clavier->is_pressed(AZERTY::K_L)) {
            y2 = (y2 + SPEED) % HEIGHT;
        }
        if (clavier->is_pressed(AZERTY::K_M)) {
            x2 = (x2 + SPEED) % WIDTH;
        }
	
}

void DungeonExplorer::mobs_action(){
	
}
