/* Copyright (C) 2014   Susu Dong
   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely.
*/


#include "Door.h"
#include "SDL.h"

Door::Door():SDLGameObject(){};

Door::~Door(){};

// Load door info
void Door::load(const LoaderParams* param) { SDLGameObject::load(param);}

void Door::draw() { SDLGameObject::draw();}

// Door does not need to animate by time. The animation is fired by collision
void Door::update() { m_currentRow++; }

void Door::clean() {}

void Door::setFrame(int newFrame) { m_currentFrame = newFrame; }

void Door::setRow(int newRow) { m_currentRow = newRow; }

SDLGameObject* DoorCreator::createGameObject() const{ return new Door();}

DoorCreator::DoorCreator() {}

DoorCreator::~DoorCreator() {}