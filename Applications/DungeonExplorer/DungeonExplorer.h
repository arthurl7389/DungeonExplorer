#ifndef DUNGEONEXPLORER_H
#define DUNGEONEXPLORER_H

#include <drivers/Clavier.h>
#include <drivers/EcranBochs.h>

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
public:
	void start();
	void init(EcranBochs*,Clavier*,ui16_t,ui16_t);
	void player1_action(int,int);
	void player2_action(int,int);
	void mobs_action();
};
#endif
