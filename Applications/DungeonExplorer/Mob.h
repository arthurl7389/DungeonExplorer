#ifndef MOB_H
#define MOB_H

#include <sextant/types.h>

class Player;

/**
 * @file Mob.h
 * @class Mob
 * @brief Une classe pour gérer les mobs.
 */


class Mob {
    int x;
    int y;
    int pv = 10;
    ui16_t WIDTH;
	ui16_t HEIGHT;
	char SPEED;
    int player_id;
    Player* player1;
    Player* player2;
    int mobCount;
    Mob** mobs;
public:
    void init(int, int, ui16_t, ui16_t, char, Player*, Player*, int, Mob**);
    Player* nearestPlayer();
    int distanceSquareToPlayer(Player*);
    bool canGoUp();
    bool canGoDown();
    bool canGoRight();
    bool canGoLeft();
    bool canMoveY();
    void action();
    void attacked(int);
    int getX() { return x; }
    int getY() { return y; }
    int getPV();
    void setPV(int);
};
#endif
