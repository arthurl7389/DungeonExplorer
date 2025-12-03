#include "Mob.h"
#include "Player.h"

void Mob::init(int x, int y, ui16_t w, ui16_t h, char sp, Player* p1, Player* p2, int mc, Mob** m) {
    this->x = x;
    this->y = y;
    WIDTH = w;
    HEIGHT = h;
    SPEED = sp;
    player1 = p1;
    player2 = p2;
    mobCount = mc;
    mobs = m;
    this->setPV(100);
}

void Mob::action() {
    Player* nearest = nearestPlayer();
    if (distanceSquareToPlayer(nearest) < 1000) {
        nearest->kill(); 
    }
    if (nearest->getX() < x && canGoLeft()) {
        x -= SPEED;
        if (x < 0) x += WIDTH;
    } else if (nearest->getX() > x && canGoRight()) {
        x = (x + SPEED) % WIDTH;
    }
    if (nearest->getY() < y && canGoDown()) {
        y -= SPEED;
        if (y < 0) y += HEIGHT;
    } else if (nearest->getY() > y && canGoUp()) {
        y = (y + SPEED) % HEIGHT;
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