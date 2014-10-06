/* Copyright (C) 2014   Susu Dong
   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely.
*/
#include "Player.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Game.h"


Player::Player(/*int level, int HP, int Attack, int Defence, int gold, int experience, int yellow, int red, int blue*/):SDLGameObject(){
	              this->level = 1;
                  this->HP = 500;
				  this->attack = 10;
				  this->defence = 10;
				  this->gold = 0;
				  this->experience = 0;
				  this->yellowKey = 0;
				  this->redKey = 0;
				  this->blueKey = 0;
				  this->canOpenGreenDoor = true;
 }

Player::~Player(){};

void Player::load(const LoaderParams* param) {
   SDLGameObject::load(param);
}

void Player::draw() {
	SDLGameObject::draw();
}

void Player::update() {
	m_currentFrame = int((SDL_GetTicks() / 100) % 4);
}

void Player::clean() {}

void Player::setFrame(int newFrame) { m_currentFrame = newFrame;  }

void Player::setRow(int newRow) { m_currentRow = newRow; }

void Player::increaseX() { m_x+= 32; update();}

void Player::increaseY() { m_y+= 32; update();}

void Player::decreaseX() { m_x-= 32; update();}

void Player::decreaseY() { m_y-= 32; update();}

int Player::getLevel() { return level; }

int Player::getHP(){ return HP; }

int Player::getAttack() { return attack; }

int Player::getDefence() { return defence; }

int Player::getGold() { return gold; }

int Player::getExperience() { return experience; }

int Player::getYellowKey() { return yellowKey; }

int Player::getRedKey() { return redKey; }

int Player::getBlueKey() { return blueKey; }

bool Player::getGreenDoor() { return canOpenGreenDoor; }

void Player::setX(int x) { m_x = x; }

void Player::setY(int y) { m_y = y; }

void Player::setGreenDoor() { canOpenGreenDoor = true; }

// Update player's level
bool Player::setLevel(int level) {
	this->level = level;
	return true;
}

// Update player's HP
bool Player::setHP(int hp) {
     if(HP + hp < 0) {
		 return false;
	 }
	 HP += hp;
	 return true;
}

// Update player attack after consuming jewels
bool Player::setAttack(int attack) {
	if(this->attack + attack < 0) {
		return false;
	}
	this->attack += attack;
	return true;
}

// Update player defence after consuming jewels
bool Player::setDefence(int defence) {
	if(this->defence + defence < 0) {
		return false;
	}
	this->defence += defence;
	return true;
}

// Update player's gold after defeating enemies
bool Player::setGold(int gold) {
	if(this->gold + gold < 0) {
		return false;
	}
	this->gold += gold;
	return true;
}

// Update player's experience after defeating enemies
bool Player::setExperience(int experience) {
	if(this->experience + experience < 0) {
		return false;
	}
	this->experience += experience;
	return true;
}

bool Player::setYellowKey(int key) {
	if(this->yellowKey + key < 0) {
		return false;
	}
	this->yellowKey += key;
	return true;
}

bool Player::setRedKey(int key) {
	if(this->redKey + key < 0) {
		return false;
	}
	this->redKey += key;
	return true;
}

bool Player::setBlueKey(int key) {
	if(this->blueKey + key < 0) {
		return false;
	}
	this->blueKey += key;
	return true;
}

// Player Creator!
SDLGameObject* PlayerCreator::createGameObject() const{
      return new Player();
}