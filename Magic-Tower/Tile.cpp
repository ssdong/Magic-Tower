/* Copyright (C) 2014   Susu Dong
   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely.
*/
#include "Tile.h"
#include "SDL.h"


Tile::Tile():SDLGameObject(){};

Tile::~Tile(){};

// Load tile info
void Tile::load(const LoaderParams* param) { SDLGameObject::load(param);}

void Tile::draw() { SDLGameObject::draw();}

void Tile::update() {}

void Tile::clean() {}

void Tile::setFrame(int newFrame) { m_currentFrame = newFrame;  }

void Tile::setRow(int newRow) { m_currentRow = newRow; }

SDLGameObject* TileCreator::createGameObject() const{ return new Tile(); }

TileCreator::TileCreator() {}

TileCreator::~TileCreator() {}