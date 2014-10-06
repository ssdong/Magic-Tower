/* Copyright (C) 2014   Susu Dong
   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely.
*/

#include "GameObjectFactory.h"
#include <iostream>

GameObjectFactory::GameObjectFactory() {}

GameObjectFactory::~GameObjectFactory() {}

GameObjectFactory* GameObjectFactory::instance = nullptr;

// Singleton factory !
GameObjectFactory* GameObjectFactory::Instance() {
	if(instance == nullptr) {
		instance = new GameObjectFactory();
		return instance;
	}
    return instance;
}

// Store object creator function
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

// Return the corresponding creator functions
SDLGameObject* GameObjectFactory::create(std::string typeID) {
	std::map<std::string, BaseCreator*>::iterator it = creators.find(typeID);

	if(it == creators.end()) { // map reaches its end
		std::cout << "Could not find type: " << typeID << std::endl; 
		return nullptr;
	}
	
	BaseCreator* creator = it->second;
	return creator->createGameObject();
}