#ifndef GAME
#define GAME

#include "Map.h"
#include "Player.h"
#include "Geometry/GlObject.h"

#include <list>

const int mapW = 129, mapH = 129;

class Game
{
	private:
		static Game gameInstance;
		Game() : worldMap(mapW, mapH) {} // private so that it can't be called
		Game(Game const&) = delete;
		Game& operator=(Game const&) = delete;

		Map worldMap;
		
		Player *player;

		std::list<GlObject*> objectList;

	public:
		static Game& Instance() {return gameInstance;}
		void initGame();

		void addObject(GlObject *o);

		void render();

		Map& getMap();
		Player& getPlayer();
};


#endif