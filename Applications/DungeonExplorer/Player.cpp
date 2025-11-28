#include "Player.h"

void Player::init(Clavier* c, ui16_t w, ui16_t h, int pId) {
    x = 0;
    y = 0;
    clavier = c;
    WIDTH = w;
    HEIGHT = h;
    player_id = pId;
}

void Player::action(bool pressed[4]) {
    if (pressed[0]) {
        y -= SPEED;
        if (y < 0) y += HEIGHT;
    }
    if (pressed[1]) {
        x -= SPEED;
        if (x < 0) x += WIDTH;
    }
    if (pressed[2]) {
        y = (y + SPEED) % HEIGHT;
    }
    if (pressed[3]) {
        x = (x + SPEED) % WIDTH;
    }
}