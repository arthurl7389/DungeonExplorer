#ifndef PLAYER_H
#define PLAYER_H

#include <drivers/Clavier.h>
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
public:
    void init(int, int, Clavier*, ui16_t, ui16_t, char, int, int, Mob**, Player*);
    void action(bool pressed[5]);
    int getX() { return x; }
    int getY() { return y; }
    bool canGoUp();
    bool canGoDown();
    bool canGoLeft();
    bool canGoRight();
    int getAttack();
    void setAttack(int);
};
#endif
