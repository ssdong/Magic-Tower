#ifndef __GAMEOBJECTFACTORY_H__
#define __GAMEOBJECTFACTORY_H__
#include <string>
#include <map>
#include "SDLGameObject.h"


class BaseCreator {
public:
   virtual SDLGameObject* createGameObject() const = 0;
   virtual ~BaseCreator() {}
};


class GameObjectFactory {
public:
	static GameObjectFactory* Instance();
	bool registerType(std::string typeID, BaseCreator* creator);
	SDLGameObject* create(std::string typeID);
	~GameObjectFactory();

private:
	static GameObjectFactory* instance;
	GameObjectFactory();
	std::map<std::string, BaseCreator*> creators;
};

#endif