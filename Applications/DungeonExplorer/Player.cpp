#include "Player.h"
#include "Mob.h"

void Player::init(int x, int y,Clavier* c, ui16_t w, ui16_t h, char sp, int pId, int mc, Mob** m, Player* p) {
    this->x = x;
    this->y = y;
    clavier = c;
    WIDTH = w;
    HEIGHT = h;
    SPEED = 3*sp;
    player_id = pId;
    mobCount = mc;
    mobs = m;
    ally = p;
    this->setAttack(6);
    alive = true;
}

void Player::action(bool pressed[5]) {
    if (pressed[0] && canGoDown()) {
        y -= SPEED;
        if (y < 0) y += HEIGHT;
    }
    if (pressed[1] && canGoLeft()) {
        x -= SPEED;
        if (x < 0) x += WIDTH;
    }
    if (pressed[2] && canGoUp()) {
        y = (y + SPEED) % HEIGHT;
    }
    if (pressed[3] && canGoRight()) {
        x = (x + SPEED) % WIDTH;
    }
    if (pressed[4]) {
        for (int i=0; i<mobCount; i++) {
            if (mobs[i]->distanceSquareToPlayer(this) < 4900) {
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

bool Player::canGoRight() {
    if (ally->getX() - x > 0 && ally->getX() - x < 50) {
        if ((ally->getY() - y) * (ally->getY() - y) < 2000) {
            return false;
        }
    }
    for (int i=0; i<mobCount; i++) {
        if (mobs[i]->getPV() > 0 && mobs[i]->getX() - x > 0 && mobs[i]->getX() - x < 50) {
            if ((mobs[i]->getY() - y) * (mobs[i]->getY() - y) < 2000) {
                return false;
            }
        }
    }
    return true;
}

bool Player::canGoLeft() {
    if (ally->getX() - x < 0 && ally->getX() - x > -50) {
        if ((ally->getY() - y) * (ally->getY() - y) < 2000) {
            return false;
        }
    }
    for (int i=0; i<mobCount; i++) {
        if (mobs[i]->getPV() > 0 && mobs[i]->getX() - x < 0 && mobs[i]->getX() - x > -50) {
            if ((mobs[i]->getY() - y) * (mobs[i]->getY() - y) < 2000) {
                return false;
            }
        }
    }
    return true;
}

bool Player::canGoUp() {
    if (ally->getY() - y > 0 && ally->getY() - y < 50) {
        if ((ally->getX() - x) * (ally->getX() - x) < 2000) {
            return false;
        }
    }
    for (int i=0; i<mobCount; i++) {
        if (mobs[i]->getPV() > 0 && mobs[i]->getY() - y > 0 && mobs[i]->getY() - y < 50) {
            if ((mobs[i]->getX() - x) * (mobs[i]->getX() - x) < 2000) {
                return false;
            }
        }
    }
    return true;
}

bool Player::canGoDown() {
    if (ally->getY() - y < 0 && ally->getY() - y > -50) {
        if ((ally->getX() - x) * (ally->getX() - x) < 2000) {
            return false;
        }
    }
    for (int i=0; i<mobCount; i++) {
        if (mobs[i]->getPV() > 0 && mobs[i]->getY() - y < 0 && mobs[i]->getY() - y > -50) {
            if ((mobs[i]->getX() - x) * (mobs[i]->getX() - x) < 2000) {
                return false;
            }
        }
    }
    return true;
}