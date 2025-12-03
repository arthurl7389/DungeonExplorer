#include "DungeonExplorer.h"

void DungeonExplorer::init(EcranBochs* vga,Clavier* c,ui16_t w,ui16_t h) {
    ecran=vga;
	clavier=c;
	WIDTH=w;
	HEIGHT=h;
    mobCount = 2;
    player1.init(200, 150, clavier, WIDTH, HEIGHT, SPEED, 0, mobCount, mobs);
    player2.init(400, 150, clavier, WIDTH, HEIGHT, SPEED, 1, mobCount, mobs);
    mob1.init(350, 150, WIDTH, HEIGHT, SPEED, &player1, &player2, mobCount, mobs);
    mob2.init(450, 250, WIDTH, HEIGHT, SPEED, &player1, &player2, mobCount, mobs);
    mobs[0] = &mob1;
    mobs[1] = &mob2;
}

// 1 : un thread par mov joueur, un pour l'affichage du monde
// 2 : on modifie le monde dynamiquement, localement
// commence simple, après rend les choses plus compliqué, 
void DungeonExplorer::start() {
    while (true) {
        bool pressed1[5] = {
            clavier->is_pressed(AZERTY::K_Z),
            clavier->is_pressed(AZERTY::K_Q),
            clavier->is_pressed(AZERTY::K_S),
            clavier->is_pressed(AZERTY::K_D),
            clavier->is_pressed(AZERTY::K_C)
        };

        bool pressed2[5] = {
            clavier->is_pressed(AZERTY::K_O),
            clavier->is_pressed(AZERTY::K_K),
            clavier->is_pressed(AZERTY::K_L),
            clavier->is_pressed(AZERTY::K_M),
            clavier->is_pressed(AZERTY::K_N)
        };
        player1.action(pressed1);
        player2.action(pressed2);
        
        for (int i = 0; i < mobCount; i++) {
            if (mobs[i]->getPV() > 0) {
                mobs[i]->action();
            }
        }

		ecran->clear(1);
		ecran->plot_sprite(sprite_data_player1, SPRITE_WIDTH, SPRITE_HEIGHT, player1.getX(), player1.getY());
		ecran->plot_sprite(sprite_data_player2, SPRITE_WIDTH, SPRITE_HEIGHT, player2.getX(), player2.getY());
        for (int i = 0; i < mobCount; i++) {
            if (mobs[i]->getPV() > 0) {
                ecran->plot_sprite(sprite_data_skeleton, SPRITE_WIDTH, SPRITE_HEIGHT, mobs[i]->getX(), mobs[i]->getY());
            }
        }
		ecran->swapBuffer();
	}
}
