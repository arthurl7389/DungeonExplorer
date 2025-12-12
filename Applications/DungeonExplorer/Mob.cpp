#include "Mob.h"
#include "Player.h"

void Mob::init(int x, int y, ui16_t w, ui16_t h, char sp, Player* p1, Player* p2, int mc, Mob** m, int wc, Wall** wls, int* ex, int* ey) {
    this->x = x;
    this->y = y;
    WIDTH = w;
    HEIGHT = h;
    SPEED = sp;
    player1 = p1;
    player2 = p2;
    mobCount = mc;
    mobs = m;
    wallCount = wc;
    walls = wls;
    this->setPV(100);
    ecran_x = ex;
    ecran_y = ey;
}

void Mob::action() {
    Player* nearest = nearestPlayer();
    if (distanceSquareToPlayer(nearest) < 2500) {
        nearest->kill(); 
    }
    if (nearest->getX() < x && canGoLeft()) {
        x -= SPEED;
        if (x < *ecran_x) x = *ecran_x;
    } else if (nearest->getX() > x && canGoRight()) {
        x += SPEED;
        if (x > *ecran_x + WIDTH - 64) x = *ecran_x + WIDTH - 64;
    }
    if (nearest->getY() < y && canGoDown()) {
        y -= SPEED;
        if (y < *ecran_y) y = *ecran_y;
    } else if (nearest->getY() > y && canGoUp()) {
        y += SPEED;
        if (y > *ecran_y + HEIGHT - 64) y = *ecran_y + HEIGHT - 64;
    }
}

Player* Mob::nearestPlayer() {
    int dist1 = distanceSquareToPlayer(player1);
    int dist2 = distanceSquareToPlayer(player2);
    if ((dist1 < dist2 && player1->isAlive()) || !player2->isAlive()) {
        return player1;
    } else {
        return player2;
    }
}

int Mob::distanceSquareToPlayer(Player* player) {
    return (player->getX() - x) * (player->getX() - x) + (player->getY() - y) * (player->getY() - y);
}

bool Mob::canGoRight() {
    for (int i=0; i<mobCount; i++) {
        if (mobs[i] != this && mobs[i]->getPV() > 0 && mobs[i]->getX() - x > 0 && mobs[i]->getX() - x < 50) {
            if ((mobs[i]->getY() - y) * (mobs[i]->getY() - y) < 2500) {
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

bool Mob::canGoLeft() {
    for (int i=0; i<mobCount; i++) {
        if (mobs[i] != this && mobs[i]->getPV() > 0 && mobs[i]->getX() - x < 0 && mobs[i]->getX() - x > -50) {
            if ((mobs[i]->getY() - y) * (mobs[i]->getY() - y) < 2500) {
                return false;
            }
        }
    }
    for (int i=0; i<wallCount; i++) {
        if (walls[i]->getX2() - x < 0 && walls[i]->getX2() - x > -5) {
            if (walls[i]->getY1() - 60 < y && walls[i]->getY2() > y) {
                return false;
            }
        }
    }
    return true;
}

bool Mob::canGoUp() {
    for (int i=0; i<mobCount; i++) {
        if (mobs[i] != this && mobs[i]->getPV() > 0 && mobs[i]->getY() - y > 0 && mobs[i]->getY() - y < 50) {
            if ((mobs[i]->getX() - x) * (mobs[i]->getX() - x) < 2500) {
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

bool Mob::canGoDown() {
    for (int i=0; i<mobCount; i++) {
        if (mobs[i] != this && mobs[i]->getPV() > 0 && mobs[i]->getY() - y < 0 && mobs[i]->getY() - y > -50) {
            if ((mobs[i]->getX() - x) * (mobs[i]->getX() - x) < 2500) {
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

void Mob::attacked(int damage) {
    if (damage < pv) {
        pv -= damage;
    } else {
        pv = 0;
    }

}

int Mob::getPV() {
    return pv;
}

void Mob::setPV(int p) {
    pv = p;
}

bool Mob::activated() {
    return pv > 0 && getX() >= *ecran_x && getX() < *ecran_x + WIDTH && getY() >= *ecran_y && getY() < *ecran_y + HEIGHT;
    //return pv > 0 && getX() >= *ecran_x && getX() < *ecran_x + WIDTH - 64 && getY() >= *ecran_y && getY() < *ecran_y + HEIGHT - 64;
}