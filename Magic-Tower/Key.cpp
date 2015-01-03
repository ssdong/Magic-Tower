/* Copyright (C) 2014   Susu Dong
   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely.
*/
#include "Key.h"
#include "SDL.h"
#include "Game.h"
#include "TextureManager.h"

Key::Key():SDLGameObject(){};

Key::~Key(){};

// Load key info
void Key::load(const LoaderParams* param) { SDLGameObject::load(param);}

void Key::draw() { SDLGameObject::draw();}

void Key::update() {}

void Key::collide(SDLGameObject* player) {
	Position p(player->getX() / 32, player->getY() / 32);
	textureManager::Instance()->drawMessage("key", p, TheGame::Instance()->getRenderer(),TheGame::Instance()->getCurrentFloor(),player, TheGame::Instance()->getFont());
}

void Key::clean() {}

void Key::setFrame(int newFrame) { m_currentFrame = newFrame;  }

void Key::setRow(int newRow) { m_currentRow = newRow; }

SDLGameObject* KeyCreator::createGameObject() const{ return new Key();}

KeyCreator::KeyCreator() {}

KeyCreator::~KeyCreator() {}