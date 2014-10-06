/* Copyright (C) 2014   Susu Dong
   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely.
*/

#include "Stair.h"
#include "SDL.h"

Stair::Stair():SDLGameObject(){};

Stair::~Stair(){};

// Load stair info
void Stair::load(const LoaderParams* param) { SDLGameObject::load(param);}

void Stair::draw() { SDLGameObject::draw();}

void Stair::update() {}

void Stair::clean() {}

void Stair::setFrame(int newFrame) { m_currentFrame = newFrame;  }

void Stair::setRow(int newRow) { m_currentRow = newRow; }

SDLGameObject* StairCreator::createGameObject() const{ return new Stair();}

StairCreator::StairCreator() {}

StairCreator::~StairCreator() {}