/* Copyright (C) 2014   Susu Dong
   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely.
*/

#include "Floor.h"
#include "Door.h"
#include "Player.h"
#include "SDL.h"
#include "Game.h"

Door::Door():SDLGameObject(){};

Door::~Door(){};

// Load door info
void Door::load(const LoaderParams* param) { SDLGameObject::load(param);}

void Door::draw() { SDLGameObject::draw();}

// Door does not need to animate by time. The animation is fired by collision
void Door::update() { m_currentRow++; }

void Door::collide(SDLGameObject* p) {
	 Player* player = dynamic_cast<Player*>(p);
	 Position p(player->getX() / 32, player->getY() / 32);
	 // Yellow door
     if(color == "yellow") {
	    // If there is no more yellow keys
		if(!player->getYellowKey()) return;
		player->setYellowKey(-1);
	 }
	 // Red door
	 else if(color == "red") {
		// If there is no more red keys
		if(!player->getRedKey()) return;
		player->setRedKey(-1);
	 }
	 // Green door
	 else if(color == "green") {
		// If cannot open green door
		if(!player->getGreenDoor()) return;
	 }
	 // Blue door
	 else {
		 // If there is no more blue keys
		 if(!player->getBlueKey()) return;
		 player->setBlueKey(-1);
	 }

	 SDLGameObject* door = TheGame::Instance()->getCurrentFloor()->elements[p];
	 while(m_currentRow != 3) {
		   door->update();
		   Game::Instance()->render();
	 }
	 // Delete door from unordered_map
	 delete door;
	 // Erase from the map
	 Game::Instance()->getCurrentFloor()->elements.erase(p);
	 return;
}

void Door::clean() {}

void Door::setFrame(int newFrame) { m_currentFrame = newFrame; }

void Door::setRow(int newRow) { m_currentRow = newRow; }

SDLGameObject* DoorCreator::createGameObject() const{ return new Door();}

DoorCreator::DoorCreator() {}

DoorCreator::~DoorCreator() {}