/* 
   Floor.cpp and Floor.h

   Copyright (C) 2014   Susu Dong
   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:

   1. The origin of this source code must not be misrepresented; you must not
      claim that you wrote the original source code. If you use this source code
      in a product, an acknowledgment in the product documentation would be
      appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
      misrepresented as being the original source code.

   3. This notice may not be removed or altered from any source distribution.

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
	// Render enemies
    for(std::vector<SDLGameObject*>::iterator i = enemies.begin(); i != enemies.end(); ++i) {
		if((*i) != nullptr) {
		   (*i)->draw();
		}
	}
	// Render doors
	for(std::vector<SDLGameObject*>::iterator i = doors.begin(); i != doors.end(); ++i) {
		if((*i) != nullptr) {
		   (*i)->draw();
		}
	}
	// Render keys
	for(std::vector<SDLGameObject*>::iterator i = keys.begin(); i != keys.end(); ++i) {
		if((*i) != nullptr) {
		   (*i)->draw();
		}
	}
	// Render jewels
	for(std::vector<SDLGameObject*>::iterator i = jewels.begin(); i != jewels.end(); ++i) {
		if((*i) != nullptr) {
		   (*i)->draw();
		}
	}
	// Render medicines
	for(std::vector<SDLGameObject*>::iterator i = medicines.begin(); i != medicines.end(); ++i) {
		if((*i) != nullptr) {
		   (*i)->draw();
		}
	}
	// Render weapons
	for(std::vector<SDLGameObject*>::iterator i = weapons.begin(); i != weapons.end(); ++i) {
		if((*i) != nullptr) {
		   (*i)->draw();
		}
	}
	// Render stairs
	for(std::vector<SDLGameObject*>::iterator i = stairs.begin(); i != stairs.end(); ++i) {
		if((*i) != nullptr) {
		   (*i)->draw();
		}
	}
}

void Floor::cleanUp() {
	// Delete map
	for(std::vector<std::vector<SDLGameObject*> >::iterator i = map.begin(); i != map.end(); ++i) {
		for(std::vector<SDLGameObject*>::iterator j = (*i).begin(); j != (*i).end(); ++j) {
			delete(*j);
		}
	}
	// Delete enemies
	for(std::vector<SDLGameObject*>::iterator i = enemies.begin(); i != enemies.end(); ++i) {
		delete(*i);
	}
	// Delete doors
	for(std::vector<SDLGameObject*>::iterator i = doors.begin(); i != doors.end(); ++i) {
		delete(*i);
	}
	// Delete jewels
	for(std::vector<SDLGameObject*>::iterator i = jewels.begin(); i != jewels.end(); ++i) {
		delete(*i);
	}
	// Delete keys
	for(std::vector<SDLGameObject*>::iterator i = keys.begin(); i != keys.end(); ++i) {
		delete(*i);
	}
	// Delete medicines
	for(std::vector<SDLGameObject*>::iterator i = medicines.begin(); i != medicines.end(); ++i) {
		delete(*i);
	}
	// Delete weapons
	for(std::vector<SDLGameObject*>::iterator i = weapons.begin(); i != weapons.end(); ++i) {
		delete(*i);
	}
	// Delete stairs
	for(std::vector<SDLGameObject*>::iterator i = stairs.begin(); i != stairs.end(); ++i) {
		delete(*i);
	}
}

