#include "DungeonExplorer.h"
#include "ThreadBackground.h"
#include "ThreadDisplay.h"

void DungeonExplorer::init(EcranBochs* vga,Clavier* c,ui16_t w,ui16_t h) {
    ecran=vga;
	clavier=c;
	WIDTH=w;
	HEIGHT=h;
    mobCount = 2;
    set_screen_position(0,0);
    player1.init(100, 100, clavier, WIDTH, HEIGHT, SPEED, 0, mobCount, mobs, &player2, wallCount, walls, &ecran_x, &ecran_y);
    player2.init(100, 200, clavier, WIDTH, HEIGHT, SPEED, 1, mobCount, mobs, &player1, wallCount, walls, &ecran_x, &ecran_y);
    mob1.init(450, 150, WIDTH, HEIGHT, SPEED, &player1, &player2, mobCount, mobs, wallCount, walls, &ecran_x, &ecran_y);
    mob2.init(450, 200, WIDTH, HEIGHT, SPEED, &player1, &player2, mobCount, mobs, wallCount, walls, &ecran_x, &ecran_y);
    mobs[0] = &mob1;
    mobs[1] = &mob2;
    wallCount = 5;
    wallRight.init(0, 0, 20, 1000, WIDTH, HEIGHT, &ecran_x, &ecran_y);
    wallLeft.init(780, 0, 800, 1000, WIDTH, HEIGHT, &ecran_x, &ecran_y);
    wallTop.init(0, 0, 800, 20, WIDTH, HEIGHT, &ecran_x, &ecran_y);
    wallBottom.init(0, 980, 800, 1000, WIDTH, HEIGHT, &ecran_x, &ecran_y);
    wall1.init(220, 0, 240, 300, WIDTH, HEIGHT, &ecran_x, &ecran_y);
    walls[0] = &wallRight;
    walls[1] = &wallLeft;
    walls[2] = &wallTop;
    walls[3] = &wallBottom;
    walls[4] = &wall1;
}

void DungeonExplorer::start() {
    Semaphore sem(1);
    ThreadBackground tBackground(&sem, this);
    ThreadDisplay tDisplay(&sem,this);
    tBackground.start();
    tDisplay.start();
    while(true);
}

int DungeonExplorer::mobs_alive() {
    int nb_alive = 0;
    for (int i=0; i<mobCount; i++) {
        if (mobs[i]->getPV() != 0) {
            nb_alive += 1;
        }
    }
    return nb_alive;
}

void DungeonExplorer::set_screen_position(int x, int y) {
    ecran_x = x;
    ecran_y = y;
}

void DungeonExplorer::update_screen_position() {
    int delta_x = 0;
    int delta_y = 0;
    if (player1.isAlive()) {
        if (player1.getX() > ecran_x + WIDTH*4/5) {
            delta_x += SPEED;
        }
        else if (player1.getX() < ecran_x + WIDTH/5 - 64) {
            delta_x -= SPEED;
        }
        if (player1.getY() > ecran_y + HEIGHT*3/4) {
            delta_y += SPEED;
        }
        else if (player1.getY() < ecran_y + HEIGHT/5 - 64) {
            delta_y -= SPEED;
        }
    }
    if (player2.isAlive()) {
        if (player2.getX() > ecran_x + WIDTH*4/5) {
            delta_x += SPEED;
        }
        else if (player2.getX() < ecran_x + WIDTH/5 - 64) {
            delta_x -= SPEED;
        }
        if (player2.getY() > ecran_y + HEIGHT*3/4) {
            delta_y += SPEED;
        }
        else if (player2.getY() < ecran_y + HEIGHT/4 - 64) {
            delta_y -= SPEED;
        }
    }
    ecran_x += delta_x;
    ecran_y += delta_y;
}

bool DungeonExplorer::inGame(){
    return (player1.isAlive() || player2.isAlive()) && mobs_alive() != 0;
}

void DungeonExplorer::backendCalculPosition(){
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
    if (player1.isAlive()) {
        player1.action(pressed1);
    }
    if (player2.isAlive()) {
        player2.action(pressed2);
    }
        
    for (int i = 0; i < mobCount; i++) {
        if (mobs[i]->activated()) {
            mobs[i]->action();
        }
    }
}

void DungeonExplorer::frontendAffichageInGame(){
    ecran->clear(1);
    update_screen_position();
    if (player1.isAlive()) {
    	ecran->plot_sprite(sprite_data_player1, SPRITE_WIDTH, SPRITE_HEIGHT, player1.getX()-ecran_x, player1.getY()-ecran_y);
    }    
    if (player2.isAlive()) {
    	ecran->plot_sprite(sprite_data_player2, SPRITE_WIDTH, SPRITE_HEIGHT, player2.getX()-ecran_x, player2.getY()-ecran_y);
    }
    for (int i = 0; i < mobCount; i++) {
        if (mobs[i]->activated()) {
            ecran->plot_sprite(sprite_data_skeleton, SPRITE_WIDTH, SPRITE_HEIGHT, mobs[i]->getX()-ecran_x, mobs[i]->getY()-ecran_y);
        }
    }
    for (int i = 0; i < wallCount; i++) {
        int w = walls[i]->X2onScreen() - walls[i]->X1onScreen();
        int h = walls[i]->Y2onScreen() - walls[i]->Y1onScreen();
        if (w != 0 && h != 0) {
            ecran->plot_rectangle(walls[i]->X1onScreen(),walls[i]->Y1onScreen(),w,h,15);
        }
    }
	ecran->swapBuffer();
}

void DungeonExplorer::frontendAffichageEnd(){
    ecran->clear(1);
    if (player1.isAlive() || player2.isAlive()) {
        ecran->plot_sprite(victoire, 194, 40, 223, 180);
    } else {
        ecran->plot_sprite(gameover, 289, 40, 175, 180);
    }
    ecran->swapBuffer();
}