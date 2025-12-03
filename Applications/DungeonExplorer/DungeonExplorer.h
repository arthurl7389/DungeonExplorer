#ifndef DUNGEONEXPLORER_H
#define DUNGEONEXPLORER_H

#include <drivers/Clavier.h>
#include <drivers/EcranBochs.h>
#include <sextant/sprite.h>
#include "Player.h"
#include "Mob.h"

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
	Mob* mobs[2] = { &mob1, &mob2};
public:
	void init(EcranBochs*,Clavier*,ui16_t,ui16_t);
	void start();
};
#endif
