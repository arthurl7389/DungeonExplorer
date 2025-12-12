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
	int mobCount = 14;
	Mob mob1;
	Mob mob2;
	Mob mob3;
	Mob mob4;
	Mob mob5;
	Mob mob6;
	Mob mob7;
	Mob mob8;
	Mob mob9;
	Mob mob10;
	Mob mob11;
	Mob mob12;
	Mob mob13;
	Mob mob14;
	Mob* mobs[14] = { &mob1, &mob2, &mob3, &mob4, &mob5, &mob6, &mob7, &mob8, &mob9, &mob10, &mob11, &mob12, &mob13, &mob14 };
	int wallCount = 12;
	Wall wallRight;
	Wall wallLeft;
	Wall wallTop;
	Wall wallBottom;
	Wall wall1;
	Wall wall2;
	Wall wall3;
	Wall wall4;
	Wall wall5;	
	Wall wall6;
	Wall wall7;
	Wall wall8;
	Wall* walls[12] = { &wallRight, &wallLeft, &wallTop, &wallBottom, &wall1, &wall2, &wall3, &wall4, &wall5, &wall6, &wall7, &wall8 };
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
