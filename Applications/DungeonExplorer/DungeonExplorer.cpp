#include "DungeonExplorer.h"
#include <drivers/EcranBochs.h>
#include <sextant/sprite.h>
#include <drivers/timer.h>

void DungeonExplorer::init(EcranBochs* vga,Clavier* c,ui16_t w,ui16_t h) {
    ecran=vga;
	clavier=c;
	WIDTH=w;
	HEIGHT=h;
    player1.init(200, 150, clavier, WIDTH, HEIGHT, SPEED, 0);
    player2.init(400, 150, clavier, WIDTH, HEIGHT, SPEED, 1);
}

// 1 : un thread par mov joueur, un pour l'affichage du monde
// 2 : on modifie le monde dynamiquement, localement
// commence simple, après rend les choses plus compliqué, 
void DungeonExplorer::start() {
    Mob mob1;
    mob1.init(350, 150, WIDTH, HEIGHT, SPEED, &player1, &player2);
    while (true) {
        bool pressed1[4] = {
            clavier->is_pressed(AZERTY::K_Z),
            clavier->is_pressed(AZERTY::K_Q),
            clavier->is_pressed(AZERTY::K_S),
            clavier->is_pressed(AZERTY::K_D)
        };

        bool pressed2[4] = {
            clavier->is_pressed(AZERTY::K_O),
            clavier->is_pressed(AZERTY::K_K),
            clavier->is_pressed(AZERTY::K_L),
            clavier->is_pressed(AZERTY::K_M)
        };
        player1.action(pressed1);
        player2.action(pressed2);
        mob1.action();
		ecran->clear(1);
		ecran->plot_sprite(sprite_data_player1, SPRITE_WIDTH, SPRITE_HEIGHT, player1.getX(), player1.getY());
		ecran->plot_sprite(sprite_data_player2, SPRITE_WIDTH, SPRITE_HEIGHT, player2.getX(), player2.getY());
		ecran->plot_sprite(sprite_data_skeleton, SPRITE_WIDTH, SPRITE_HEIGHT, mob1.getX(), mob1.getY());
		ecran->swapBuffer();
	}
}
