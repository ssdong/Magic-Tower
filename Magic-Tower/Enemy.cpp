/* Copyright (C) 2014   Susu Dong
   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely.
*/
#include "Enemy.h"
#include "SDL.h"
#include "Player.h"
#include "TextureManager.h"
#include "Game.h"
#include "Floor.h"


Enemy::Enemy():SDLGameObject(){};

Enemy::~Enemy(){};

// Load enemy info
void Enemy::load(const LoaderParams* param) { SDLGameObject::load(param);}

void Enemy::draw() { SDLGameObject::draw();}

// Update frame to make enemy "alive"
void Enemy::update() { m_currentFrame = int((SDL_GetTicks() / 100) % 4); }

void Enemy::clean() {}

void Enemy::setFrame(int newFrame) { m_currentFrame = newFrame;  }

void Enemy::setRow(int newRow) { m_currentRow = newRow; }

void Enemy::setHP(int hp) { this->HP = hp; }

void Enemy::setAttack(int attack) { this->attack = attack; }

void Enemy::setDefence(int defence) { this->defence = defence; }

void Enemy::setGold(int gold) { this->gold = gold; }

void Enemy::setExperience(int experience) { this->experience = experience; }

int Enemy::getHP(){ return HP; }

int Enemy::getAttack() { return attack; }

int Enemy::getDefence() { return defence; }

int Enemy::getGold() { return gold; }

int Enemy::getExperience() { return experience; }

SDLGameObject* EnemyCreator::createGameObject() const{ return new Enemy();}

EnemyCreator::EnemyCreator() {}

EnemyCreator::~EnemyCreator() {}

bool Enemy::canFight(Player* player) {
	 int PlayerHP = player->getHP();
	 int PlayerAttack = player->getAttack();
	 int PlayerDefence = player->getDefence();
	 int EnemyHP = HP;
	 int EnemyAttack = attack;
	 int EnemyDefence = defence;
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

bool Enemy::collideHelper(int &playerHP, int &enemyHP, int P_E_damage, int E_P_damage, unsigned int& lastTime) {
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

void Enemy::collide(SDLGameObject* p) {
	 if(!canFight(dynamic_cast<Player*>(p))) return;
	 else {
		  // Yes! Can defeat!
		  Player* player = dynamic_cast<Player*>(p);
		  Position p(player->getX() / 32, player->getY() / 32);
		  int PlayerHP = player->getHP();
	      int EnemyHP = HP;
          // Calculate player to enemy's damage and vice versa
		  int P_E_damage = (100.0 / (100 + defence)) * player->getAttack();
		  int E_P_damage = (100.0 / (100 + player->getDefence())) * attack;
          // Start fighting!
		  unsigned int lastTime = SDL_GetTicks();
		  while(true) {
			 if(collideHelper(PlayerHP,EnemyHP,P_E_damage, E_P_damage,lastTime)) {
				// Print the winning message
				textureManager::Instance()->drawMessage("win", p, TheGame::Instance()->getRenderer(),TheGame::Instance()->getCurrentFloor(),player, TheGame::Instance()->getFont());
				// Rest player status
				dynamic_cast<Player*>(player)->setHP(PlayerHP - player->getHP());
				dynamic_cast<Player*>(player)->setGold(gold);
				dynamic_cast<Player*>(player)->setExperience(experience);
				SDLGameObject* enemy = TheGame::Instance()->getCurrentFloor()->elements[p];
				delete (enemy);
				Game::Instance()->getCurrentFloor()->elements.erase(p);
				break;
			 }
			 else {
				// Print the fighting message
                textureManager::Instance()->drawMessage( "fight", p, TheGame::Instance()->getRenderer(),TheGame::Instance()->getCurrentFloor(),player, TheGame::Instance()->getFont());
		     }
	      }
}