/* 
   Weapon.cpp and Weapon.h

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