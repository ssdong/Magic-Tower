/* 
   CollisionDetector.cpp and CollisionDetector.h

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

#include "CollisionDetecter.h"
#include "SDLGameObject.h"
#include "Player.h"
#include "Tile.h"
#include "Stair.h"
#include "Enemy.h"
#include "TextureManager.h"
#include "Game.h"

Collision* Collision::instance = nullptr;

Collision::Collision() {}

Collision::~Collision() {}

Collision* Collision::Instance() {
	if(instance == nullptr) {
		instance = new Collision();
	}
	return instance;
}

bool Collision::detectKey(std::vector<SDLGameObject* >* keys, SDLGameObject* player, char direction, int offset, int& position) {
	int x = player->getX();
	int y = player->getY();
	if(direction == 'N') {
		y -= offset;
	}
	else if(direction == 'W') {
		x -= offset;
	}
	else if(direction == 'S') {
		y += offset;
	}
	else {
		x += offset;
	}
	for(int i = 0; i < keys->size(); i++) {
		if((*keys)[i] != nullptr && (*keys)[i]->getX() == x && (*keys)[i]->getY() == y) {
			// Collision!
			if((*keys)[i]->getColor() == "yellow") {
				dynamic_cast<Player*>(player)->setYellowKey(1);
			}
			else if((*keys)[i]->getColor() == "red") {
				dynamic_cast<Player*>(player)->setRedKey(1);
			}
			else {
				dynamic_cast<Player*>(player)->setBlueKey(1);
			}
			position = i;
			return true;
		}
	}
	return false;
}

bool Collision::detectJewel(std::vector<SDLGameObject* >* jewels, SDLGameObject* player, char direction, int offset, int& position) {
	int x = player->getX();
	int y = player->getY();
	if(direction == 'N') {
		y -= offset;
	}
	else if(direction == 'W') {
		x -= offset;
	}
	else if(direction == 'S') {
		y += offset;
	}
	else {
		x += offset;
	}
	for(int i = 0; i < jewels->size(); i++) {
		if((*jewels)[i] != nullptr && (*jewels)[i]->getX() == x && (*jewels)[i]->getY() == y) {
			// Collision!
			if((*jewels)[i]->getColor() == "red") {
				dynamic_cast<Player*>(player)->setAttack(3);
			}
			else if ((*jewels)[i]->getColor() == "blue"){
				dynamic_cast<Player*>(player)->setDefence(2);
			}
			else if ((*jewels)[i]->getColor() == "green"){
				dynamic_cast<Player*>(player)->setAttack(7);
			}
			else if ((*jewels)[i]->getColor() == "yellow"){
				dynamic_cast<Player*>(player)->setDefence(5);
			}
			else {

			}
			position = i;
			return true;
		}
	}
	return false;
}

bool Collision::detectMedicine(std::vector<SDLGameObject* >* medicines, SDLGameObject* player, char direction, int offset, int& position) {
	int x = player->getX();
	int y = player->getY();
	if(direction == 'N') {
		y -= offset;
	}
	else if(direction == 'W') {
		x -= offset;
	}
	else if(direction == 'S') {
		y += offset;
	}
	else {
		x += offset;
	}
	for(int i = 0; i < medicines->size(); i++) {
		if((*medicines)[i] != nullptr && (*medicines)[i]->getX() == x && (*medicines)[i]->getY() == y) {
			// Collision!
			if((*medicines)[i]->getColor() == "red") {
				dynamic_cast<Player*>(player)->setHP(50);
			}
			else if((*medicines)[i]->getColor() == "blue"){
				dynamic_cast<Player*>(player)->setHP(100);
			}
			else if((*medicines)[i]->getColor() == "green"){
				dynamic_cast<Player*>(player)->setHP(150);
			}
			else if((*medicines)[i]->getColor() == "yellow"){
				dynamic_cast<Player*>(player)->setHP(150);
			}
			else {
			}
			position = i;
			return true;
		}
	}
	return false;
}

bool Collision::detectDoorExist(std::vector<SDLGameObject* >* doors, SDLGameObject* player, char direction, int offset, int& position) {
	int x = player->getX();
	int y = player->getY();
	if(direction == 'N') {
		y -= offset;
	}
	else if(direction == 'W') {
		x -= offset;
	}
	else if(direction == 'S') {
		y += offset;
	}
	else {
		x += offset;
	}
	for(int i = 0; i < doors->size(); i++) {
		if((*doors)[i] != nullptr && (*doors)[i]->getX() == x && (*doors)[i]->getY() == y) {
			position = i;
			return true;
		} 
	}
	return false;
}

bool Collision::detectDoor(std::vector<SDLGameObject* >* doors, SDLGameObject* player, char direction, int offset, int position) {
    if((*doors)[position]->getColor() == "yellow") {
		if(dynamic_cast<Player*>(player)->getYellowKey() == 0) {
			return true;
		}
		if((*doors)[position]->getRow() == 3) {
			dynamic_cast<Player*>(player)->setYellowKey(-1);
			delete (*doors)[position];
			(*doors)[position] = nullptr;
			return true;
		}
		else {
			(*doors)[position]->update();
			return false;
		}
	}
	else if((*doors)[position]->getColor() == "red") {
		if(dynamic_cast<Player*>(player)->getRedKey() == 0) {
			return true;
		}
		if((*doors)[position]->getRow() == 3) {
			dynamic_cast<Player*>(player)->setRedKey(-1);
			delete (*doors)[position];
			(*doors)[position] = nullptr;
			return true;
		}
		else {
			(*doors)[position]->update();
			return false;
		}
	}
	else if((*doors)[position]->getColor() == "green") {
		if(!dynamic_cast<Player*>(player)->getGreenDoor()) {
			return true;
		}
		if((*doors)[position]->getRow() == 3) {
			delete (*doors)[position];
			(*doors)[position] = nullptr;
			return true;
		}
		else {
			(*doors)[position]->update();
			return false;
		}
	}
	else {
		if(dynamic_cast<Player*>(player)->getBlueKey() == 0) {
			return true;
		}
		if((*doors)[position]->getRow() == 3) {
			dynamic_cast<Player*>(player)->setBlueKey(-1);
			delete (*doors)[position];
			(*doors)[position] = nullptr;
			return true;
		}
		else {
			(*doors)[position]->update();
			return false;
		}
	}
}

bool Collision::detectEnemyExist(std::vector<SDLGameObject* >* enemies, SDLGameObject* player, char direction, int offset, int& position) {
	int x = player->getX();
	int y = player->getY();
	if(direction == 'N') {
		y -= offset;
	}
	else if(direction == 'W') {
		x -= offset;
	}
	else if(direction == 'S') {
		y += offset;
	}
	else {
		x += offset;
	}
	for(int i = 0; i < enemies->size(); i++) {
		if((*enemies)[i] != nullptr && (*enemies)[i]->getX() == x && (*enemies)[i]->getY() == y) {
			position = i;
			return true;
		} 
	}
	return false;
}

bool Collision::detectCanFightWithEnemy(std::vector<SDLGameObject* >* enemies, SDLGameObject* player, char direction, int offset, int position) {
	int PlayerHP = dynamic_cast<Player*>(player)->getHP();
	int PlayerAttack = dynamic_cast<Player*>(player)->getAttack();
	int PlayerDefence = dynamic_cast<Player*>(player)->getDefence();
	int EnemyHP = dynamic_cast<Enemy*>((*enemies)[position])->getHP();
	int EnemyAttack = dynamic_cast<Enemy*>((*enemies)[position])->getAttack();
	int EnemyDefence = dynamic_cast<Enemy*>((*enemies)[position])->getDefence();
	if(PlayerAttack < EnemyDefence) {
		return false;
	}
	int P_E_damage = (100.0 / (100 + EnemyDefence)) * PlayerAttack;
	int E_P_damage = (100.0 / (100 + PlayerDefence)) * EnemyAttack;
	while(true) {
		EnemyHP -= P_E_damage;
		if(EnemyHP <= 0) {
			return true;
		}
		PlayerHP -= E_P_damage;
		if(PlayerHP <= 0) {
			return false;
		}
	}
}

bool Collision::fight(std::vector<SDLGameObject* >* enemies, SDLGameObject* player, char direction, int offset, int position,SDL_Renderer* pRenderer, TTF_Font* font,
	                  int &playerHP, int &enemyHP, int P_E_damage, int E_P_damage, unsigned int &lastTime) {
	 unsigned int currentTime = SDL_GetTicks();
	 if(currentTime > lastTime + 200) {
		 enemyHP -= P_E_damage;
		 playerHP -= E_P_damage;
		 if(enemyHP <= 0) {
			 return true;
		 }
		 lastTime = currentTime;
		 return false;
	 }
	 else {
		 return false;
	 }
}

bool Collision::detectWall(std::vector<std::vector<SDLGameObject*> > *map, SDLGameObject* player, char direction, int offset) {
	int x = player->getX();
	int y = player->getY();
	if(direction == 'N') {
		y -= offset;
	}
	else if(direction == 'W') {
		x -= offset;
	}
	else if(direction == 'S') {
		y += offset;
	}
	else {
		x += offset;
	}
	for(std::vector<std::vector<SDLGameObject*> >::iterator i = map->begin(); i != map->end(); ++i) {
		for(std::vector<SDLGameObject*>::iterator j = (*i).begin(); j != (*i).end(); ++j) {
			if((*j)->getX() == x && (*j)->getY() == y) {
				if(dynamic_cast<Tile*>(*j)->type == 'B') {
					return true;
				}
			}
		}
	}

	return false;
}

bool Collision::detectStair(std::vector<SDLGameObject* >* stairs, SDLGameObject* player, char direction, int offset, char& stairType) {
	int x = player->getX();
	int y = player->getY();
	if(direction == 'N') {
		y -= offset;
	}
	else if(direction == 'W') {
		x -= offset;
	}
	else if(direction == 'S') {
		y += offset;
	}
	else {
		x += offset;
	}
	for(std::vector<SDLGameObject*>::iterator i = stairs->begin(); i != stairs->end(); ++i) {
		if((*i)->getX() == x && (*i)->getY() == y) {
			stairType = dynamic_cast<Stair*>(*i)->type;
			return true;
		}
	}
}