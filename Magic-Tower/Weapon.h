#ifndef __WEAPON_H__ 
#define __WEAPON_H__

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class LoaderParams;

class Weapon : public SDLGameObject {
public:
	int num;
	char type;
	Weapon();
	virtual ~Weapon();
	void load(const LoaderParams* param);
	void draw();
    void update();
	void clean();
	void setFrame(int newFrame);
	void setRow(int newRow);
};

class WeaponCreator : public BaseCreator {
public:
	 WeaponCreator();
	 ~WeaponCreator();
     SDLGameObject* createGameObject() const;

};

#endif