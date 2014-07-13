/*
   SDLGameObject.cpp and SDLGameObject.h uses codes 
   from "SDL Game Development"
*/
#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject():GameObject(){}

void SDLGameObject::load(const LoaderParams* param) {
	m_x = param->getX();
	m_y = param->getY();
	m_width = param->getWidth();
	m_height = param->getHeight();
	m_textureID = param->getID();
	m_currentFrame = param->getFrame();
	m_currentRow = param->getRow();
}

void SDLGameObject::draw() {
	textureManager::Instance()->drawFrame(m_textureID,m_x,m_y,m_width,m_height,
		                                  m_currentRow,m_currentFrame,TheGame::Instance()->getRenderer());
}

void SDLGameObject::update() {}

void SDLGameObject::clean() {}

SDLGameObject::~SDLGameObject() {}

void SDLGameObject::setFrame(int newFrame) {}

void SDLGameObject::setRow(int newRow) {}

void SDLGameObject::increaseX() {}

void SDLGameObject::increaseY() {}

void SDLGameObject::decreaseX() {}

void SDLGameObject::decreaseY() {}

void SDLGameObject::setColor(std::string color) { this->color = color; }

std::string SDLGameObject::getColor() { return color; }

int SDLGameObject::getX() { return m_x; }

int SDLGameObject::getY() { return m_y; }

int SDLGameObject::getRow() { return m_currentRow; }

int SDLGameObject::getFrame() { return m_currentFrame; }