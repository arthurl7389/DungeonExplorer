#include "Player.h"

void Player::init(Clavier* c, ui16_t w, ui16_t h, int id) {
    x = 0;
    y = 0;
    clavier = c;
    WIDTH = w;
    HEIGHT = h;
    id = id;
}

void Player::action() {
    if (clavier->is_pressed(controls[id][0])) {
        y -= SPEED;
        if (y < 0) y += HEIGHT;
    }
    if (clavier->is_pressed(controls[id][1])) {
        x -= SPEED;
        if (x < 0) x += WIDTH;
    }
    if (clavier->is_pressed(controls[id][2])) {
        y = (y + SPEED) % HEIGHT;
    }
    if (clavier->is_pressed(controls[id][3])) {
        x = (x + SPEED) % WIDTH;
    }
}