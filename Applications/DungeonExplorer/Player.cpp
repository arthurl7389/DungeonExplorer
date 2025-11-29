#include "Player.h"
#include "Mob.h"

void Player::init(int x, int y,Clavier* c, ui16_t w, ui16_t h, char sp, int pId, int mc, Mob** m) {
    this->x = x;
    this->y = y;
    clavier = c;
    WIDTH = w;
    HEIGHT = h;
    SPEED = 2*sp;
    player_id = pId;
    mobCount = mc;
    mobs = m;
    this->setAttack(6);
}

void Player::action(bool pressed[5]) {
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
    if (pressed[4]) {
        for (int i=0; i<mobCount; i++) {
            if (mobs[i]->distanceSquareToPlayer(this) < 3600) {
                mobs[i]->attacked(attack);
            }
        }
    }
}

int Player::getAttack() {
    return attack;
}

void Player::setAttack(int a) {
    attack = a;
}