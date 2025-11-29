#include "Mob.h"
#include "Player.h"

void Mob::init(int x, int y, ui16_t w, ui16_t h, char sp, Player* p1, Player* p2) {
    this->x = x;
    this->y = y;
    WIDTH = w;
    HEIGHT = h;
    SPEED = sp;
    player1 = p1;
    player2 = p2;
    this->setPV(100);
}

void Mob::action() {
    Player* nearest = nearestPlayer();
    if (distanceSquareToPlayer(nearest) < 2500) {
        return; 
    }
    if (nearest->getX() < x) {
        x -= SPEED;
        if (x < 0) x += WIDTH;
    } else if (nearest->getX() > x) {
        x = (x + SPEED) % WIDTH;
    }
    if (nearest->getY() < y) {
        y -= SPEED;
        if (y < 0) y += HEIGHT;
    } else if (nearest->getY() > y) {
        y = (y + SPEED) % HEIGHT;
    }
}

Player* Mob::nearestPlayer() {
    int dist1 = (player1->getX() - x) * (player1->getX() - x) + (player1->getY() - y) * (player1->getY() - y);
    int dist2 = (player2->getX() - x) * (player2->getX() - x) + (player2->getY() - y) * (player2->getY() - y);
    if (dist1 < dist2) {
        return player1;
    } else {
        return player2;
    }
}

int Mob::distanceSquareToPlayer(Player* player) {
    return (player->getX() - x) * (player->getX() - x) + (player->getY() - y) * (player->getY() - y);
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