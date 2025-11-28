#ifndef MOB_H
#define MOB_H

#include <sextant/types.h>
#include "Player.h"

/**
 * @file Mob.h
 * @class Mob
 * @brief Une classe pour gérer les mobs.
 */


class Mob {
    int x;
    int y;
    ui16_t WIDTH;
	ui16_t HEIGHT;
	char SPEED;
    int player_id;
    Player* player1;
    Player* player2;
public:
    void init(int, int, ui16_t, ui16_t, char, Player*, Player*);
    Player nearestPlayer();
    int distanceSquareToPlayer(Player*);
    void action();
    int getX() { return x; }
    int getY() { return y; }
};
#endif
