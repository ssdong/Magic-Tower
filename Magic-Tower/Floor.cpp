/* Copyright (C) 2014   Susu Dong
   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely.
*/

#include "Floor.h"
#include "SDLGameObject.h"

Floor::Floor() {}

Floor::~Floor() { cleanUp();}

void Floor::render() {
	// Render map
	for(std::vector<std::vector<SDLGameObject*> >::iterator i = map.begin(); i != map.end(); ++i) {
		for(std::vector<SDLGameObject*>::iterator j = (*i).begin(); j != (*i).end(); ++j) {
			   (*j)->draw();
		}
	}
	// Render game elements
	for(std::unordered_map<Position*, SDLGameObject*, PositionHash>::iterator i = elements.begin(); i != elements.end(); ++i) {
		i->second->draw();
	}
   
}

void Floor::cleanUp() {
	// Delete map
	for(std::vector<std::vector<SDLGameObject*> >::iterator i = map.begin(); i != map.end(); ++i) {
		for(std::vector<SDLGameObject*>::iterator j = (*i).begin(); j != (*i).end(); ++j) {
			delete(*j);
		}
	}
	// Delete game elements
	for(std::unordered_map<Position*, SDLGameObject*, PositionHash>::iterator i = elements.begin(); i != elements.end(); ++i) {
		delete i->first;
		delete i->second;
	}
}
