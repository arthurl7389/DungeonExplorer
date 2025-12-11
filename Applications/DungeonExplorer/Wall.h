#ifndef WALL_H
#define WALL_H

#include <sextant/types.h>

/**
 * @file Wall.h
 * @class Wall
 * @brief Une classe pour gérer les murs.
 */


class Wall {
    int x1;
    int y1;
    int x2;
    int y2;
    ui16_t WIDTH;
	ui16_t HEIGHT;
    int* ecran_x;
    int* ecran_y;
public:
    void init(int, int, int, int, ui16_t, ui16_t, int*, int*);
    int getX1() { return x1; }
    int getY1() { return y1; }
    int getX2() { return x2; }
    int getY2() { return y2; }
    int X1onScreen();
    int Y1onScreen();
    int X2onScreen();
    int Y2onScreen();
};
#endif
