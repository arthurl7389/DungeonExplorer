#include "Player.h"
#include "Mob.h"

void Player::init(int x, int y,Clavier* c, ui16_t w, ui16_t h, char sp, int pId, int mc, Mob** m, Player* p, int wc, Wall** wls, int* ex, int* ey) {
    this->x = x;
    this->y = y;
    clavier = c;
    WIDTH = w;
    HEIGHT = h;
    SPEED = 5*sp;
    player_id = pId;
    mobCount = mc;
    mobs = m;
    wallCount = wc;
    walls = wls;
    ally = p;
    this->setAttack(6);
    alive = true;
    ecran_x = ex;
    ecran_y = ey;
}

void Player::action(bool pressed[5]) {
    if (pressed[0] && canGoDown()) {
        y -= SPEED;
        if (y < *ecran_y) y = *ecran_y;
    }
    if (pressed[1] && canGoLeft()) {
        x -= SPEED;
        if (x < *ecran_x) x = *ecran_x;
    }
    if (pressed[2] && canGoUp()) {
        y += SPEED;
        if (y > *ecran_y + HEIGHT - 64) y = *ecran_y + HEIGHT - 64;
    }
    if (pressed[3] && canGoRight()) {
        x += SPEED;
        if (x > *ecran_x + WIDTH - 64) x = *ecran_x + WIDTH - 64;
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
    if (ally->isAlive() && ally->getX() - x > 0 && ally->getX() - x < 50) {
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
    for (int i=0; i<wallCount; i++) {
        if (walls[i]->getX1() - x > 0 && walls[i]->getX1() - x < 65) {
            if (walls[i]->getY1() - 60 < y && walls[i]->getY2() > y) {
                return false;
            }
        }
    }
    return true;
}

bool Player::canGoLeft() {
    if (ally->isAlive() && ally->getX() - x < 0 && ally->getX() - x > -50) {
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
    for (int i=0; i<wallCount; i++) {
        int test = wallCount;
        if (walls[i]->getX2() - x < 0 && walls[i]->getX2() - x > -5) {
            if (walls[i]->getY1() - 60 < y && walls[i]->getY2() > y) {
                return false;
            }
        }
    }
    return true;
}

bool Player::canGoUp() {
    if (ally->isAlive() && ally->getY() - y > 0 && ally->getY() - y < 50) {
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
    for (int i=0; i<wallCount; i++) {
        if (walls[i]->getY1() - y > 0 && walls[i]->getY1() - y < 65) {
            if (walls[i]->getX1() - 60 < x && walls[i]->getX2() > x) {
                return false;
            }
        }
    }
    return true;
}

bool Player::canGoDown() {
    if (ally->isAlive() && ally->getY() - y < 0 && ally->getY() - y > -50) {
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
    for (int i=0; i<wallCount; i++) {
        if (walls[i]->getY2() - y < 0 && walls[i]->getY2() - y > -5) {
            if (walls[i]->getX1() - 60 < x && walls[i]->getX2() > x) {
                return false;
            }
        }
    }
    return true;
}