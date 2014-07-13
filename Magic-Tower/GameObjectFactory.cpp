/*
  GameObjectFactory.cpp and GameObjectFactory.h use the code 
   from the book "SDL Game Development"

*/

#include "GameObjectFactory.h"
#include <iostream>

GameObjectFactory::GameObjectFactory() {}

GameObjectFactory::~GameObjectFactory() {}

GameObjectFactory* GameObjectFactory::instance = nullptr;

GameObjectFactory* GameObjectFactory::Instance() {
	if(instance == nullptr) {
		instance = new GameObjectFactory();
		return instance;
	}
    return instance;
}

bool GameObjectFactory::registerType(std::string typeID, BaseCreator* creator) {
	std::map<std::string, BaseCreator*>::iterator it = creators.find(typeID);

	// if the type is alreday registered, do nothing
	if(it != creators.end()) {
		delete creator;
		return false;
	}
	creators[typeID] = creator;
	return true;
}

SDLGameObject* GameObjectFactory::create(std::string typeID) {
	std::map<std::string, BaseCreator*>::iterator it = creators.find(typeID);

	if(it == creators.end()) {
		std::cout << "Could not find type: " << typeID << std::endl; 
		return nullptr;
	}
	
	BaseCreator* creator = it->second;
	return creator->createGameObject();
}