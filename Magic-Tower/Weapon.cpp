/* Copyright (C) 2014   Susu Dong
   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely.
*/
#include "Weapon.h"
#include "SDL.h"


Weapon::Weapon():SDLGameObject(){};

Weapon::~Weapon(){};

void Weapon::load(const LoaderParams* param) {
   SDLGameObject::load(param);
}

void Weapon::draw() {
	SDLGameObject::draw();
}

void Weapon::update() {}

void Weapon::clean() {}

void Weapon::setFrame(int newFrame) { m_currentFrame = newFrame;  }

void Weapon::setRow(int newRow) { m_currentRow = newRow; }



SDLGameObject* WeaponCreator::createGameObject() const{
       return new Weapon();
}

WeaponCreator::WeaponCreator() {}

WeaponCreator::~WeaponCreator() {}