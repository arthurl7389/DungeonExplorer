#ifndef PLAYER_H
#define PLAYER_H

#include <drivers/Clavier.h>


/**
 * @file Player.h
 * @class Player
 * @brief Une classe pour gérer les joueurs.
 */


class Player {
    //AZERTY::scancodes controls[2][4];
    int x;
    int y;
    Clavier* clavier;
    ui16_t WIDTH;
	ui16_t HEIGHT;
	const char SPEED = 1;
    int player_id;
public:
    void init(int, int, Clavier*, ui16_t, ui16_t, int);
    void action(bool pressed[4]);
    int getX() { return x; }
    int getY() { return y; }
};
#endif
