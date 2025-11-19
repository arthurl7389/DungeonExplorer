#ifndef DUNGEONEXPLORER_H
#define DUNGEONEXPLORER_H

#include <drivers/Clavier.h>

/**
 * @file DungeonExplorer.h
 * @class DungeonExplorer
 * @brief Un explorateur de donjon en coop contre des mobs.
 */



class DungeonExplorer {
	Clavier *clavier;
	Ecran *ecran;
public:
	void start();
	void init(Ecran*,Clavier*);
};
#endif
