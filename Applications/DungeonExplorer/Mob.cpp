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
    moving = false;
    Player* nearest = nearestPlayer();
    if (distanceSquareToPlayer(nearest) < 3000) {
        nearest->kill(); 
    }
    if (nearest->getX() < x && canGoLeft()) {
        x -= SPEED;
        if (x < *ecran_x) x = *ecran_x;
        moving = true;
        leftFacing = true;
    } else if (nearest->getX() > x && canGoRight()) {
        x += SPEED;
        if (x > *ecran_x + WIDTH - 64) x = *ecran_x + WIDTH - 64;
        moving = true;
        leftFacing = false;
    }
    if (nearest->getY() < y && canGoUp()) {
        y -= SPEED;
        if (y < *ecran_y) y = *ecran_y;
        moving = true;
    } else if (nearest->getY() > y && canGoDown()) {
        y += SPEED;
        if (y > *ecran_y + HEIGHT - 64) y = *ecran_y + HEIGHT - 64;
        moving = true;
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
            if (walls[i]->getY1() - 60 < y && walls[i]->getY2() > y + 5) {
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
            if (walls[i]->getY1() - 60 < y && walls[i]->getY2() > y + 5) {
                return false;
            }
        }
    }
    return true;
}

bool Mob::canGoDown() {
    for (int i=0; i<mobCount; i++) {
        if (mobs[i] != this && mobs[i]->getPV() > 0 && mobs[i]->getY() - y > 0 && mobs[i]->getY() - y < 50) {
            if ((mobs[i]->getX() - x) * (mobs[i]->getX() - x) < 2500) {
                return false;
            }
        }
    }
    for (int i=0; i<wallCount; i++) {
        if (walls[i]->getY1() - y > 0 && walls[i]->getY1() - y < 65) {
            if (walls[i]->getX1() - 60 < x && walls[i]->getX2() > x + 1) {
                return false;
            }
        }
    }
    return true;
}

bool Mob::canGoUp() {
    for (int i=0; i<mobCount; i++) {
        if (mobs[i] != this && mobs[i]->getPV() > 0 && mobs[i]->getY() - y < 0 && mobs[i]->getY() - y > -50) {
            if ((mobs[i]->getX() - x) * (mobs[i]->getX() - x) < 2500) {
                return false;
            }
        }
    }
    for (int i=0; i<wallCount; i++) {
        if (walls[i]->getY2() - y < 0 && walls[i]->getY2() - y > -5) {
            if (walls[i]->getX1() - 60 < x && walls[i]->getX2() > x + 1) {
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
    return pv > 0 && ((player1->isAlive() && !wallBetween(player1)) || (player2->isAlive() && !wallBetween(player2))) && getX() >= *ecran_x - WIDTH && getX() < *ecran_x + WIDTH && getY() >= *ecran_y - HEIGHT && getY() < *ecran_y + HEIGHT;
}

bool Mob::wallBetween(Player* player) {
    bool crossed1 = false;
    bool crossed2 = false;
    for (int i=0; i<wallCount; i++) {
        for (float t=0; t<=1.0; t+=0.01) {
            float x_middle1 = t * x + (1-t) * player->getX();
            float y_middle1 = t * y + (1-t) * player->getY();
            if (x_middle1 >= walls[i]->getX1() && x_middle1 <= walls[i]->getX2() && y_middle1 >= walls[i]->getY1() && y_middle1 <= walls[i]->getY2()) {
                crossed1 = true;
            }
        }
        for (float t=0; t<=1.0; t+=0.01) {
            float x_middle2 = t * (x+63) + (1-t) * (player->getX()+63);
            float y_middle2 = t * (y+63) + (1-t) * (player->getY()+63);
            if (x_middle2 >= walls[i]->getX1() && x_middle2 <= walls[i]->getX2() && y_middle2 >= walls[i]->getY1() && y_middle2 <= walls[i]->getY2()) {
                crossed2 = true;
            }
        }
        if (crossed1 && crossed2) {
            return true;
        }
    }
    return false;
}

bool Mob::printable() {
    return pv > 0 && getX() >= *ecran_x - WIDTH && getX() < *ecran_x + WIDTH && getY() >= *ecran_y - HEIGHT && getY() < *ecran_y + HEIGHT;
}