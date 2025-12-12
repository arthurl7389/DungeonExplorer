#ifndef DUNGEONEXPLORER_H
#define DUNGEONEXPLORER_H

#include <drivers/Clavier.h>
#include <drivers/EcranBochs.h>
#include <sextant/sprite.h>
#include "Player.h"
#include "Mob.h"
#include "Wall.h"
#include <sextant/Synchronisation/Semaphore/Semaphore.h>


/**
 * @file DungeonExplorer.h
 * @class DungeonExplorer
 * @brief Un explorateur de donjon en coop contre des mobs.
 */



class DungeonExplorer {
	Clavier *clavier;
	EcranBochs *ecran;
	ui16_t WIDTH;
	ui16_t HEIGHT;
	const char SPEED = 1;
	Player player1;
	Player player2;
	int mobCount = 2;
	Mob mob1;
	Mob mob2;
	Mob* mobs[2] = { &mob1, &mob2 };
	int wallCount = 5;
	Wall wallRight;
	Wall wallLeft;
	Wall wallTop;
	Wall wallBottom;
	Wall wall1;
	Wall* walls[5] = { &wallRight, &wallLeft, &wallTop, &wallBottom, &wall1 };
	int ecran_x;
	int ecran_y;
	//Semaphore *mutex; // on verra après si on en a besoin ici
public:
	void init(EcranBochs*,Clavier*,ui16_t,ui16_t);
	void start();
	int mobs_alive();
	void set_screen_position(int x, int y);
	void update_screen_position();
	bool inGame();
	void backendCalculPosition();
	void frontendAffichageInGame();
	void frontendAffichageEnd();
};
#endif
