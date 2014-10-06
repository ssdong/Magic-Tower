#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__
#include <string>

class LoaderParams; 

class GameObject {
public:
	virtual void draw() = 0; 
	virtual void update() = 0;
	virtual void clean() = 0;
    // new load function
	virtual void load(const LoaderParams * param) = 0;

protected: // Changed here
	GameObject();
	virtual ~GameObject();
};

#endif