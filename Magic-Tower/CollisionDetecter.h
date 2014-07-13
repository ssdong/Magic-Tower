#ifndef __COLLISIONDETECTOR_H__
#define __COLLISIONDETECTOR_H__
#include <vector>
#include "SDL.h"
#include "SDL_ttf.h"

class SDLGameObject;

class Collision {
private:
	static Collision* instance;
	Collision();
public:
	~Collision();
	static Collision* Instance();
	bool detectKey(std::vector<SDLGameObject* >* keys, SDLGameObject* player, char direction, int offset, int& position);
	bool detectJewel(std::vector<SDLGameObject* >* jewels, SDLGameObject* player, char direction, int offset, int& position);
	bool detectMedicine(std::vector<SDLGameObject* >* medicines, SDLGameObject* player, char direction, int offset, int& position);
	bool detectDoorExist(std::vector<SDLGameObject* >* doors, SDLGameObject* player, char direction, int offset, int& position);
	bool detectDoor(std::vector<SDLGameObject* >* doors, SDLGameObject* player, char direction, int offset, int position);
	bool detectEnemyExist(std::vector<SDLGameObject* >* enemies, SDLGameObject* player, char direction, int offset, int& position);
	bool detectCanFightWithEnemy(std::vector<SDLGameObject* >* enemies, SDLGameObject* player, char direction, int offset, int position);
	bool fight(std::vector<SDLGameObject* >* enemies, SDLGameObject* player, char direction, int offset, int position, SDL_Renderer* pRenderer, TTF_Font* font, 
		       int &playerHP, int &enemyHP, int P_E_damage, int E_P_damage, unsigned int &lastTime);
	bool detectWall(std::vector<std::vector<SDLGameObject*> > *map, SDLGameObject* player, char direction, int offset);
	bool detectStair(std::vector<SDLGameObject* >* stairs, SDLGameObject* player, char direction, int offset, char& stairType);
};

#endif