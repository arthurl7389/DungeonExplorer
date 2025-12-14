#include "DungeonExplorer.h"
#include "ThreadBackground.h"
#include "ThreadDisplay.h"
#include <sextant/interruptions/handler/handler_tic.h>

void DungeonExplorer::init(EcranBochs* vga,Clavier* c,ui16_t w,ui16_t h) {
    ecran=vga;
	clavier=c;
	WIDTH=w;
	HEIGHT=h;
    sem = new Semaphore(1);
    tBackground = new ThreadBackground(sem, this);
    tDisplay = new ThreadDisplay(sem, this);
    reset(); // initialization for players and mobs
    // walls initialization
    wallRight.init(0, 0, 20, 1000, WIDTH, HEIGHT, &ecran_x, &ecran_y);
    wallLeft.init(780, 0, 800, 1000, WIDTH, HEIGHT, &ecran_x, &ecran_y);
    wallTop.init(0, 0, 800, 20, WIDTH, HEIGHT, &ecran_x, &ecran_y);
    wallBottom.init(0, 980, 800, 1000, WIDTH, HEIGHT, &ecran_x, &ecran_y);
    wall1.init(220, 0, 240, 250, WIDTH, HEIGHT, &ecran_x, &ecran_y);
    wall2.init(0, 380, 600, 400, WIDTH, HEIGHT, &ecran_x, &ecran_y);
    wall3.init(500, 400, 520, 800, WIDTH, HEIGHT, &ecran_x, &ecran_y);
    wall4.init(200, 780, 600, 800, WIDTH, HEIGHT, &ecran_x, &ecran_y);
    wall5.init(200, 630, 300, 650, WIDTH, HEIGHT, &ecran_x, &ecran_y);
    wall6.init(200, 550, 300, 570, WIDTH, HEIGHT, &ecran_x, &ecran_y);
    wall7.init(200, 550, 220, 650, WIDTH, HEIGHT, &ecran_x, &ecran_y);
    wall8.init(280, 550, 300, 650, WIDTH, HEIGHT, &ecran_x, &ecran_y);
    walls[0] = &wallRight;
    walls[1] = &wallLeft;
    walls[2] = &wallTop;
    walls[3] = &wallBottom;
    walls[4] = &wall1;
    walls[5] = &wall2;
    walls[6] = &wall3;
    walls[7] = &wall4;
    walls[8] = &wall5;
    walls[9] = &wall6;
    walls[10] = &wall7;
    walls[11] = &wall8;
}

void DungeonExplorer::start() {
    while (launchGame() == 0){ // wait for player to choose mode
        ecran->clear(1);
        ecran->plot_sprite(commands, 185, 320, 228, 5);
        ecran->plot_sprite(touches1, 217, 43, 212, 345);
        ecran->swapBuffer();
    }
    if (launchGame() == 1) { // one player mode (we kill player 2)
        onePlayerMode();
    }
    tBackground->start();
    tDisplay->start();
    while(true) {
        thread_yield();
    }
}

int DungeonExplorer::launchGame(){
    if (clavier->is_pressed(AZERTY::K_G) && clavier->is_pressed(AZERTY::K_B)) { // two players mode
        return 2;
    }
    if (clavier->is_pressed(AZERTY::K_G) && clavier->is_pressed(AZERTY::K_A)) { // one player mode
        return 1;
    }
    return 0; // no mode selected yet
}

void DungeonExplorer::onePlayerMode(){
    player2.kill(); // kill player 2 (one player mode)
}

int DungeonExplorer::mobs_alive() {
    // we check the number of mobs still alive
    int nb_alive = 0;
    for (int i=0; i<mobCount; i++) {
        if (mobs[i]->getPV() != 0) {
            nb_alive += 1;
        }
    }
    return nb_alive;
}

void DungeonExplorer::set_screen_position(int x, int y) {
    // set the screen position inside the map
    ecran_x = x;
    ecran_y = y;
}

void DungeonExplorer::update_screen_position() {
    // update the screen position based on players positions
    // if a player is too close to the edge of the screen, we move the screen in that direction
    int delta_x = 0;
    int delta_y = 0;
    if (player1.isAlive()) {
        if (player1.getX() > ecran_x + WIDTH*3/4) {
            delta_x += SPEED;
        }
        else if (player1.getX() < ecran_x + WIDTH/4 - 64) {
            delta_x -= SPEED;
        }
        if (player1.getY() > ecran_y + HEIGHT*2/3) {
            delta_y += SPEED;
        }
        else if (player1.getY() < ecran_y + HEIGHT/3 - 64) {
            delta_y -= SPEED;
        }
    }
    if (player2.isAlive()) {
        if (player2.getX() > ecran_x + WIDTH*3/4) {
            delta_x += SPEED;
        }
        else if (player2.getX() < ecran_x + WIDTH/4 - 64) {
            delta_x -= SPEED;
        }
        if (player2.getY() > ecran_y + HEIGHT*2/3) {
            delta_y += SPEED;
        }
        else if (player2.getY() < ecran_y + HEIGHT/3 - 64) {
            delta_y -= SPEED;
        }
    }
    ecran_x += 3*delta_x; // player speed is 3
    ecran_y += 3*delta_y;
}

bool DungeonExplorer::inGame(){
    // we are still in game if at least one player is alive and at least one mob is alive
    return (player1.isAlive() || player2.isAlive()) && mobs_alive() != 0;
}

void DungeonExplorer::backendCalculPosition(){
    // we get the pressed keys for both players
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
    // we update players positions based on pressed keys if they are alive
    if (player1.isAlive()) {
        player1.action(pressed1);
    }
    if (player2.isAlive()) {
        player2.action(pressed2);
    }
    // we update mobs positions if they are activated (alive, in screen and player in range)
    for (int i = 0; i < mobCount; i++) {
        if (mobs[i]->activated()) {
            mobs[i]->action();
        }
    }
}

void DungeonExplorer::frontendAffichageInGame(){
    ecran->clear(1); // clear screen with black color
    update_screen_position(); // update screen position based on players positions
    // we draw players and mobs if alive and add animations if they are moving
    if (player1.isAlive()) {
    	if (player1.isMoving()) {
    		if ((compt/300) % 2 == 0) // we change the sprite every 300 tics if moving
    			ecran->plot_sprite(sprite_data_player1, SPRITE_WIDTH, SPRITE_HEIGHT, player1.getX()-ecran_x, player1.getY()-ecran_y, player1.isLeftFacing());
    		else {
                if (player1.goVertically()) { // for player we have different running sprites for vertical and horizontal movement (vertical is prioritized)
                    ecran->plot_sprite(sprite_data_player1_vertically, SPRITE_WIDTH, SPRITE_HEIGHT, player1.getX()-ecran_x, player1.getY()-ecran_y, player1.isLeftFacing());
                } else {
        			ecran->plot_sprite(sprite_data_player1_running, SPRITE_WIDTH, SPRITE_HEIGHT, player1.getX()-ecran_x, player1.getY()-ecran_y, player1.isLeftFacing());
                }
            }
        } else {
    		ecran->plot_sprite(sprite_data_player1, SPRITE_WIDTH, SPRITE_HEIGHT, player1.getX()-ecran_x, player1.getY()-ecran_y, player1.isLeftFacing());
    	}
    }    
    if (player2.isAlive()) {
        if (player2.isMoving()) {
            if ((compt/300) % 2 == 0) // we change the sprite every 300 tics if moving
                ecran->plot_sprite(sprite_data_player2, SPRITE_WIDTH, SPRITE_HEIGHT, player2.getX()-ecran_x, player2.getY()-ecran_y, player2.isLeftFacing());
            else {
                if (player2.goVertically()) {
                    ecran->plot_sprite(sprite_data_player2_vertically, SPRITE_WIDTH, SPRITE_HEIGHT, player2.getX()-ecran_x, player2.getY()-ecran_y, player2.isLeftFacing());
                } else {
                    ecran->plot_sprite(sprite_data_player2_running, SPRITE_WIDTH, SPRITE_HEIGHT, player2.getX()-ecran_x, player2.getY()-ecran_y, player2.isLeftFacing());
                }
            }
        } else {
            ecran->plot_sprite(sprite_data_player2, SPRITE_WIDTH, SPRITE_HEIGHT, player2.getX()-ecran_x, player2.getY()-ecran_y, player2.isLeftFacing());
        }
    }
    for (int i = 0; i < mobCount; i++) {
        if (mobs[i]->printable()) {
            if (mobs[i]->isMoving() && mobs[i]->activated()) {
                if ((compt/300) % 2 == 0) // we change the sprite every 300 tics if moving
                    ecran->plot_sprite(sprite_data_skeleton, SPRITE_WIDTH, SPRITE_HEIGHT, mobs[i]->getX()-ecran_x, mobs[i]->getY()-ecran_y, mobs[i]->isLeftFacing());
                else
                    ecran->plot_sprite(sprite_data_skeleton_running, SPRITE_WIDTH, SPRITE_HEIGHT, mobs[i]->getX()-ecran_x, mobs[i]->getY()-ecran_y, mobs[i]->isLeftFacing());
            } else {
                ecran->plot_sprite(sprite_data_skeleton, SPRITE_WIDTH, SPRITE_HEIGHT, mobs[i]->getX()-ecran_x, mobs[i]->getY()-ecran_y, mobs[i]->isLeftFacing());
            }
        }
    }
    // we update the walls positions depending on new screen position and draw them
    for (int i = 0; i < wallCount; i++) {
        int w = walls[i]->X2onScreen() - walls[i]->X1onScreen();
        int h = walls[i]->Y2onScreen() - walls[i]->Y1onScreen();
        if (w != 0 && h != 0) {
            ecran->plot_rectangle(walls[i]->X1onScreen(),walls[i]->Y1onScreen(),w,h,15);
        }
    }
	ecran->swapBuffer(); // we swap the buffers to display the new frame
}

void DungeonExplorer::frontendAffichageEnd(){
    // when the game is over we display either victory or game over screen
    ecran->clear(1);
    if (player1.isAlive() || player2.isAlive()) {
        ecran->plot_sprite(victoire, 194, 40, 223, 180);
        ecran->plot_sprite(touches2, 438, 78, 101, 300);
    } else {
        ecran->plot_sprite(gameover, 289, 40, 175, 180);
        ecran->plot_sprite(touches2, 438, 78, 101, 300);
    }
    ecran->swapBuffer();
}

void DungeonExplorer::reset(){
    // lwe reset the game to initial positions (we just reset players and mobs, other variables are good)
    set_screen_position(0,0);
    player1.init(100, 100, clavier, WIDTH, HEIGHT, SPEED, 0, mobCount, mobs, &player2, wallCount, walls, &ecran_x, &ecran_y);
    player2.init(100, 200, clavier, WIDTH, HEIGHT, SPEED, 1, mobCount, mobs, &player1, wallCount, walls, &ecran_x, &ecran_y);
    mob1.init(270, 125, WIDTH, HEIGHT, SPEED, &player1, &player2, mobCount, mobs, wallCount, walls, &ecran_x, &ecran_y);
    mob2.init(730, 300, WIDTH, HEIGHT, SPEED, &player1, &player2, mobCount, mobs, wallCount, walls, &ecran_x, &ecran_y);
    mob3.init(690, 300, WIDTH, HEIGHT, SPEED, &player1, &player2, mobCount, mobs, wallCount, walls, &ecran_x, &ecran_y);
    mob4.init(600, 700, WIDTH, HEIGHT, SPEED, &player1, &player2, mobCount, mobs, wallCount, walls, &ecran_x, &ecran_y);
    mob5.init(700, 700, WIDTH, HEIGHT, SPEED, &player1, &player2, mobCount, mobs, wallCount, walls, &ecran_x, &ecran_y);
    mob6.init(650, 770, WIDTH, HEIGHT, SPEED, &player1, &player2, mobCount, mobs, wallCount, walls, &ecran_x, &ecran_y);
    mob7.init(300, 825, WIDTH, HEIGHT, SPEED, &player1, &player2, mobCount, mobs, wallCount, walls, &ecran_x, &ecran_y);
    mob8.init(300, 900, WIDTH, HEIGHT, SPEED, &player1, &player2, mobCount, mobs, wallCount, walls, &ecran_x, &ecran_y);
    mob9.init(100, 450, WIDTH, HEIGHT, SPEED, &player1, &player2, mobCount, mobs, wallCount, walls, &ecran_x, &ecran_y);
    mob10.init(225, 450, WIDTH, HEIGHT, SPEED, &player1, &player2, mobCount, mobs, wallCount, walls, &ecran_x, &ecran_y);
    mob11.init(375, 450, WIDTH, HEIGHT, SPEED, &player1, &player2, mobCount, mobs, wallCount, walls, &ecran_x, &ecran_y);
    mob12.init(375, 550, WIDTH, HEIGHT, SPEED, &player1, &player2, mobCount, mobs, wallCount, walls, &ecran_x, &ecran_y);
    mob13.init(375, 650, WIDTH, HEIGHT, SPEED, &player1, &player2, mobCount, mobs, wallCount, walls, &ecran_x, &ecran_y);
    mob14.init(100, 550, WIDTH, HEIGHT, SPEED, &player1, &player2, mobCount, mobs, wallCount, walls, &ecran_x, &ecran_y);
    mobs[0] = &mob1;
    mobs[1] = &mob2;
    mobs[2] = &mob3;
    mobs[3] = &mob4;
    mobs[4] = &mob5;
    mobs[5] = &mob6;
    mobs[6] = &mob7;
    mobs[7] = &mob8;
    mobs[8] = &mob9;
    mobs[9] = &mob10;
    mobs[10] = &mob11;
    mobs[11] = &mob12;
    mobs[12] = &mob13;
    mobs[13] = &mob14;
}