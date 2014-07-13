#ifndef __STAIR_H__ 
#define __STAIR_H__

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class LoaderParams;

class Stair : public SDLGameObject {
public:
	char type;
	Stair();
	virtual ~Stair();
	void load(const LoaderParams* param);
	void draw();
    void update();
	void clean();
	void setFrame(int newFrame);
	void setRow(int newRow);
};

class StairCreator : public BaseCreator {
public:
	 StairCreator();
	 ~StairCreator();
     SDLGameObject* createGameObject() const;

};

#endif