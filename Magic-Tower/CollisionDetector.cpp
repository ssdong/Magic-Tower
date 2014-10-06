/* Copyright (C) 2014   Susu Dong
   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely.
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

// Singleton collison detector! 
Collision* Collision::Instance() {
	if(instance == nullptr) {
		instance = new Collision();
	}
	return instance;
}


bool Collision::detectKey(std::vector<SDLGameObject* >* keys, 
	                      SDLGameObject* player, 
						  char direction, 
						  int offset, 
						  int& position) {
	// Get the new position of player
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
	// Now we iterate through the keys array to detect which key the player is trying to pick up
	// Should use a quadtree when the map is getting large.
	for(int i = 0; i < keys->size(); i++) {
		// Check if the key has already been picked by checking "nullptr"
		if((*keys)[i] != nullptr && (*keys)[i]->getX() == x && (*keys)[i]->getY() == y) {
			// Collision!
			if((*keys)[i]->getColor() == "yellow") {
				dynamic_cast<Player*>(player)->setYellowKey(1);
			}
			else if((*keys)[i]->getColor() == "red") {
				dynamic_cast<Player*>(player)->setRedKey(1);
			}
			else if((*keys)[i]->getColor() == "blue"){
				dynamic_cast<Player*>(player)->setBlueKey(1);
			}
			else {
				// TODO; add more colors if possible
			}
			// Store the position of the key in the vector to be used later
			position = i;
			return true;
		}
	}
	return false;
}


bool Collision::detectJewel(std::vector<SDLGameObject* >* jewels, 
	                        SDLGameObject* player, 
							char direction, 
							int offset, 
							int& position) {
	// Get the new position of the player
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
		// Check if the jewel has already been picked by checking "nullptr"
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
				// TODO; add more colors if possible
			}
			// Store the position of the key in the vector to be used later
			position = i;
			return true;
		}
	}
	return false;
}


bool Collision::detectMedicine(std::vector<SDLGameObject* >* medicines, 
	                           SDLGameObject* player, 
							   char direction, 
							   int offset, 
							   int& position) {
	// Get the new position of the player
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
		// Check if the medicine has already been picked by checking "nullptr"
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
				// TODO; add more colors if possible
			}
			// Store the position of the key in the vector to be used later
			position = i;
			return true;
		}
	}
	return false;
}


bool Collision::detectDoorExist(std::vector<SDLGameObject* >* doors, 
	                            SDLGameObject* player, 
								char direction, 
								int offset, 
								int& position) {
	// Get the position of the player
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
			// Store the position of the door which is being collided with the player
			position = i;
			return true;
		} 
	}
	return false;
}


bool Collision::detectDoor(std::vector<SDLGameObject* >* doors, 
	                       SDLGameObject* player, 
						   char direction, 
						   int offset, 
						   int position) {
    if((*doors)[position]->getColor() == "yellow") {
		// If the player trys to open a yellow door...
		if(dynamic_cast<Player*>(player)->getYellowKey() == 0) {
			return true;
		}
		if((*doors)[position]->getRow() == 3) {
		    // Now the door has finished opening with an animation
			dynamic_cast<Player*>(player)->setYellowKey(-1);
			delete (*doors)[position];
			(*doors)[position] = nullptr;
			return true;
		}
		else {
		    // Not finished yet
			(*doors)[position]->update();
			return false;
		}
	}
	else if((*doors)[position]->getColor() == "red") {
		// If the player trys to open a red door...
		if(dynamic_cast<Player*>(player)->getRedKey() == 0) {
			return true;
		}
		if((*doors)[position]->getRow() == 3) {
		    // Now the door has finished opening with an animation
			dynamic_cast<Player*>(player)->setRedKey(-1);
			delete (*doors)[position];
			(*doors)[position] = nullptr;
			return true;
		}
		else {
		    // Not finished yet
			(*doors)[position]->update();
			return false;
		}
	}
	else if((*doors)[position]->getColor() == "green") {
		// If the player trys to open a green door...
		if(!dynamic_cast<Player*>(player)->getGreenDoor()) {
			return true;
		}
		if((*doors)[position]->getRow() == 3) {
			// Now the door has finished opening with an animation
			delete (*doors)[position];
			(*doors)[position] = nullptr;
			return true;
		}
		else {
		    // Not finished yet
			(*doors)[position]->update();
			return false;
		}
	}
	else {
		// If the player trys to open a blue door...
		if(dynamic_cast<Player*>(player)->getBlueKey() == 0) {
			return true;
		}
		if((*doors)[position]->getRow() == 3) {
		    // Now the door has finished opening with an animation
			dynamic_cast<Player*>(player)->setBlueKey(-1);
			delete (*doors)[position];
			(*doors)[position] = nullptr;
			return true;
		}
		else {
		    // Not finished yet
			(*doors)[position]->update();
			return false;
		}
	}
}


bool Collision::detectEnemyExist(std::vector<SDLGameObject* >* enemies, 
	                             SDLGameObject* player, 
								 char direction, 
								 int offset, 
								 int& position) {
	// Get the position of the player
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
			// Store the position of the enemy which is being collided with the player
			position = i;
			return true;
		} 
	}
	return false;
}


bool Collision::detectCanFightWithEnemy(std::vector<SDLGameObject* >* enemies, 
	                                    SDLGameObject* player, 
										char direction, 
										int offset, 
										int position) {
	int PlayerHP = dynamic_cast<Player*>(player)->getHP();
	int PlayerAttack = dynamic_cast<Player*>(player)->getAttack();
	int PlayerDefence = dynamic_cast<Player*>(player)->getDefence();
	int EnemyHP = dynamic_cast<Enemy*>((*enemies)[position])->getHP();
	int EnemyAttack = dynamic_cast<Enemy*>((*enemies)[position])->getAttack();
	int EnemyDefence = dynamic_cast<Enemy*>((*enemies)[position])->getDefence();
	// Can not defeat the enemy if the player has a lower attach than the enemy's defence
	if(PlayerAttack < EnemyDefence) {
		return false;
	}
	int P_E_damage = (100.0 / (100 + EnemyDefence)) * PlayerAttack;
	int E_P_damage = (100.0 / (100 + PlayerDefence)) * EnemyAttack;
	// Keep fighting until one arises, the other falls...
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


// TODO; This function needs to be updated
bool Collision::fight(std::vector<SDLGameObject* >* enemies, 
	                  SDLGameObject* player, 
					  char direction, 
					  int offset, 
					  int position,
					  SDL_Renderer* pRenderer, 
					  TTF_Font* font,
	                  int &playerHP, 
					  int &enemyHP, 
					  int P_E_damage, 
					  int E_P_damage, 
					  unsigned int &lastTime) {
	 unsigned int currentTime = SDL_GetTicks();
	 // Each message during the fight lasts for 0.2 s
	 if(currentTime > lastTime + 200) {
		 enemyHP -= P_E_damage;
		 playerHP -= E_P_damage;
		 if(enemyHP <= 0) {
			 return true;
		 }
         // Enemy still alive, keep fight!
		 lastTime = currentTime;
		 return false;
	 }
	 else { // 0.2 s period over. Update the message!
		 return false;
	 }
}


bool Collision::detectWall(std::vector<std::vector<SDLGameObject*> > *map, 
	                       SDLGameObject* player, 
						   char direction, 
						   int offset) {
	// Get the new position of the player
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
	// Iterate through the 2D vectors of walls
	for(std::vector<std::vector<SDLGameObject*> >::iterator i = map->begin(); i != map->end(); ++i) {
		for(std::vector<SDLGameObject*>::iterator j = (*i).begin(); j != (*i).end(); ++j) {
			if((*j)->getX() == x && (*j)->getY() == y) {
				// Collision!
				if(dynamic_cast<Tile*>(*j)->type == 'B') {
					return true;
				}
			}
		}
	}
	return false;
}


bool Collision::detectStair(std::vector<SDLGameObject* >* stairs, 
	                        SDLGameObject* player, 
							char direction, 
							int offset, 
							char& stairType) {
	// Get the new position of the player
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
			// Collision!
			stairType = dynamic_cast<Stair*>(*i)->type;
			return true;
		}
	}
}