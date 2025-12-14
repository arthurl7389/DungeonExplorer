#include "Wall.h"

void Wall::init(int x1, int y1, int x2, int y2, ui16_t w, ui16_t h, int* ex, int* ey) {
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    WIDTH = w;
    HEIGHT = h;
    ecran_x = ex;
    ecran_y = ey;
}

int Wall::X1onScreen() { // we return the wall's X1 coordinate on screen, taking into account screen position and boundaries
    if (getX1() - *ecran_x < 0) {
        return 0;
    }
    if (getX1() - *ecran_x > WIDTH) {
        return WIDTH;
    }
    return getX1() - *ecran_x;
}

int Wall::Y1onScreen() {
    if (getY1() - *ecran_y < 0) {
        return 0;
    }
    if (getY1() - *ecran_y > HEIGHT) {
        return HEIGHT;
    }
    return getY1() - *ecran_y;
}

int Wall::X2onScreen() {
    int diff = getX2() - *ecran_x;
    if (getX2() - *ecran_x < 0) {
        return 0;
    }
    if (getX2() - *ecran_x > WIDTH) {
        return WIDTH;
    }
    return getX2() - *ecran_x;
}

int Wall::Y2onScreen() {
    if (getY2() - *ecran_y < 0) {
        return 0;
    }
    if (getY2() - *ecran_y > HEIGHT) {
        return HEIGHT;
    }
    return getY2() - *ecran_y;
}