#ifndef __KEY_H__ 
#define __KEY_H__

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class LoaderParams;

class Key : public SDLGameObject {
public:
	Key();
	virtual ~Key();
	void load(const LoaderParams* param);
	void draw();
    void update();
	void clean();
	void setFrame(int newFrame);
	void setRow(int newRow);
};

class KeyCreator : public BaseCreator {
public:
	 KeyCreator();
	 ~KeyCreator();
     SDLGameObject* createGameObject() const;

};

#endif