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