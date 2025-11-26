#ifndef PLAYER_H
#define PLAYER_H

#include <drivers/Clavier.h>


/**
 * @file Player.h
 * @class Player
 * @brief Une classe pour gérer les joueurs.
 */


class Player {
    int x;
    int y;
    Clavier* clavier;
    ui16_t WIDTH;
	ui16_t HEIGHT;
	const char SPEED = 1;
    int id;
    AZERTY::scancodes controls[2][4] = {
        {AZERTY::K_Z, AZERTY::K_Q, AZERTY::K_S, AZERTY::K_D}, // Player 1
        {AZERTY::K_O, AZERTY::K_K, AZERTY::K_L, AZERTY::K_M}  // Player 2
    };
public:
    void init(Clavier*, ui16_t, ui16_t, int id);
    void action();
    int getX() { return x; }
    int getY() { return y; }
};
#endif
