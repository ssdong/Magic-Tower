#ifndef __FLOOR_H__
#define __FLOOR_H__
#include <vector>
#include <unordered_map>


#include "Position.h"

class SDLGameObject;

// Floor stores elements on that floor

class Floor {

public:
	std::unordered_map<Position, SDLGameObject*, PositionHash> elements; 
	std::vector<std::vector<SDLGameObject*> > map;// Map

public:
	Floor();
	~Floor();
    
	void render();
	void cleanUp();
};
#endif