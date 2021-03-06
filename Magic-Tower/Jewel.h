#ifndef __JEWEL_H__ 
#define __JEWEL_H__

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class LoaderParams;

/*
   There are currently 6 kinds of jewels
*/

class Jewel : public SDLGameObject {
public:
	Jewel();
	virtual ~Jewel();
	void load(const LoaderParams* param);
	void draw();
    void update();
	void clean();
	void collide(SDLGameObject* player);
	void setFrame(int newFrame);
	void setRow(int newRow);
};

class JewelCreator : public BaseCreator {
public:
	 JewelCreator();
	 ~JewelCreator();
     SDLGameObject* createGameObject() const;

};

#endif