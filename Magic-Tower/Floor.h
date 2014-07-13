#ifndef __FLOOR_H__
#define __FLOOR_H__
#include <vector>

class SDLGameObject;

class Floor {
public:
	Floor();
	~Floor();
	std::vector<SDLGameObject*> medicines; // Medicine
	std::vector<SDLGameObject*> weapons; // Weapon
	std::vector<SDLGameObject*> jewels; // Jewels
	std::vector<SDLGameObject*> keys; // Key
	std::vector<SDLGameObject*> doors; // Door
	std::vector<SDLGameObject*> enemies; // Enemy	
	std::vector<SDLGameObject*> stairs; // Stairs
	std::vector<std::vector<SDLGameObject*> > map;// Map
	
	void render();
	void cleanUp();
};
#endif