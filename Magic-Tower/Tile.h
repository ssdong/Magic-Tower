#ifndef __TILE_H__ 
#define __TILE_H__

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class LoaderParams;

class Tile : public SDLGameObject {
public:
	Tile();
	virtual ~Tile();
	void load(const LoaderParams* param);
	void draw();
    void update();
	void clean();
	void setFrame(int newFrame);
	void setRow(int newRow);

	char type;
};

class TileCreator : public BaseCreator {
public:
	 TileCreator();
	 ~TileCreator();
     SDLGameObject* createGameObject() const;

};

#endif