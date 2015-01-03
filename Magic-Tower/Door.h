#ifndef __DOOR_H__ 
#define __DOOR_H__

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

/* 
   There are currently 3 kinds of doors
*/

class LoaderParams;

class Door : public SDLGameObject {
public:
	Door();
	virtual ~Door();
	void load(const LoaderParams* param);
	void draw();
    void update();
	void clean();
	void setFrame(int newFrame);
	void setRow(int newRow);
	void collide(SDLGameObject* p);
};

class DoorCreator : public BaseCreator {
public:
	 DoorCreator();
	 ~DoorCreator();
     SDLGameObject* createGameObject() const;

};

#endif