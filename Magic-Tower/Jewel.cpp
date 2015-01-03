/* Copyright (C) 2014   Susu Dong
   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely.
*/
#include "Jewel.h"
#include "SDL.h"
#include "Game.h"
#include "TextureManager.h"

Jewel::Jewel():SDLGameObject(){};

Jewel::~Jewel(){};

// Load jewel info
void Jewel::load(const LoaderParams* param) { SDLGameObject::load(param);}

void Jewel::draw() { SDLGameObject::draw(); }

void Jewel::update() {}

void Jewel::clean() {}

void Jewel::collide(SDLGameObject* player) {
	 Position p(player->getX(), player->getY());
	 textureManager::Instance()->drawMessage("jewel", p, TheGame::Instance()->getRenderer(),TheGame::Instance()->getCurrentFloor(),player, TheGame::Instance()->getFont());
}

void Jewel::setFrame(int newFrame) { m_currentFrame = newFrame;  }

void Jewel::setRow(int newRow) { m_currentRow = newRow; }

SDLGameObject* JewelCreator::createGameObject() const{ return new Jewel();}

JewelCreator::JewelCreator() {}

JewelCreator::~JewelCreator() {}