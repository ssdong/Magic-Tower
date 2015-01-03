/* Copyright (C) 2014   Susu Dong
   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely.
*/
#include "Medicine.h"
#include "SDL.h"
#include "Game.h"
#include "TextureManager.h"

Medicine::Medicine():SDLGameObject(){};

Medicine::~Medicine(){};

// Load medicine info
void Medicine::load(const LoaderParams* param) { SDLGameObject::load(param);}

void Medicine::draw() { SDLGameObject::draw();}

void Medicine::update() {}

void Medicine::clean() {}

void Medicine::collide(SDLGameObject* player) {
	 Position p(player->getX() / 32, player->getY() / 32);
	 textureManager::Instance()->drawMessage("medicine", p, TheGame::Instance()->getRenderer(),TheGame::Instance()->getCurrentFloor(),player, TheGame::Instance()->getFont());
}

void Medicine::setFrame(int newFrame) { m_currentFrame = newFrame;  }

void Medicine::setRow(int newRow) { m_currentRow = newRow; }

SDLGameObject* MedicineCreator::createGameObject() const{ return new Medicine();}

MedicineCreator::MedicineCreator() {}

MedicineCreator::~MedicineCreator() {}