#ifndef PLAYER_H
#define PLAYER_H

#include <drivers/Clavier.h>
#include "Wall.h"
class Mob;


/**
 * @file Player.h
 * @class Player
 * @brief Une classe pour gérer les joueurs.
 */


class Player {
    int x;
    int y;
    int attack = 5;
    Clavier* clavier;
    ui16_t WIDTH;
	ui16_t HEIGHT;
	char SPEED;
    int player_id;
    int mobCount;
    Mob** mobs;
    Player* ally;
    int wallCount;
    Wall** walls;
    bool alive = true;
    int* ecran_x;
    int* ecran_y;
    bool moving = false;
    bool vertically = false;
    bool leftFacing = false;
public:
    void init(int, int, Clavier*, ui16_t, ui16_t, char, int, int, Mob**, Player*, int, Wall**, int*, int*);
    void action(bool pressed[5]);
    int getX() { return x; }
    int getY() { return y; }
    bool canGoUp();
    bool canGoDown();
    bool canGoLeft();
    bool canGoRight();
    bool isAlive() { return alive; }
    void kill() { alive = false; }
    bool isMoving() { return moving; }
    bool goVertically() { return vertically; }
    bool isLeftFacing() { return leftFacing; }
};
#endif
