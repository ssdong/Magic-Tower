/* Copyright (C) 2014   Susu Dong
   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely.
*/
#include <iostream>
#include <Windows.h>

// SDL headers
#include "SDL_image.h"

// Game itself
#include "Game.h"

// TextureManager header deal with drawing pictures on screen
#include "TextureManager.h"

// SDL Game Object headers
#include "GameObjectFactory.h"
#include "SDLGameObject.h"
#include "Enemy.h"
#include "Player.h"
#include "Tile.h"
#include "Medicine.h"
#include "Jewel.h"
#include "Key.h"
#include "Door.h"
#include "Weapon.h"
#include "Stair.h"
#include "Floor.h"

#include "CollisionDetecter.h"

// Helper Class for loading datas
#include "LoaderParams.h"

// XML Parser
#include "XMLParser.h"

Game::Game():Running(true),window(nullptr),renderer(nullptr),player(nullptr){}

Game::~Game(){}

Game* Game::instance = nullptr;

// Singleton function

// Singleton game !
Game* Game::Instance() {
	if(instance == nullptr) {
		instance = new Game();
		return instance;
	}
    return instance;
}


// Initialize everything 
bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags){
	// Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		MessageBox(NULL,SDL_GetError(), "error", MB_OK);
		return false;
	}
	if((window = SDL_CreateWindow(title,xpos,ypos,width,height,flags)) == nullptr) {
		MessageBox(NULL,SDL_GetError(), "error", MB_OK);
		return false;
	}
	if((renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED)) == nullptr) {
		MessageBox(NULL,SDL_GetError(), "error", MB_OK);
		return false;
	}
	// Initialize SDL_ttf
	if(TTF_Init() == -1) {
		MessageBox(NULL,TTF_GetError(),"error",MB_OK);
		return false;
	}
	font = TTF_OpenFont("./Font.ttf",24);

	// Set SDL background color
	SDL_SetRenderDrawColor(renderer,0,0,0,0);

	// Game is running now(set Running to true)
	Running = true;


	// Load the hero sprite sheet
	if(!textureManager::Instance()->load("./img/tiledMap/hero.PNG","hero",renderer)) {
		MessageBox(NULL,"Can not load image file", "error", MB_OK);
		return false;
	}

	// Load the enemy sprite sheet
	if(!textureManager::Instance()->load("./img/tiledMap/enemy.PNG","enemy",renderer)) {
		MessageBox(NULL,"Can not load image file", "error", MB_OK);
		return false;
	}

	// Load the map sprite sheet
	if(!textureManager::Instance()->load("./img/tiledMap/terrain.PNG","terrain",renderer)) {
		MessageBox(NULL,"Can not load image file", "error", MB_OK);
		return false;
	}

	// Load the background sprite sheet
	if(!textureManager::Instance()->load("./img/tiledMap/background.PNG","background",renderer)) {
		MessageBox(NULL,"Can not load image file", "error", MB_OK);
		return false;
	}

	// Load the item sprite sheet
	if(!textureManager::Instance()->load("./img/tiledMap/item.PNG", "item", renderer)) {
		MessageBox(NULL,"Can not load image file", "error", MB_OK);
		return false;
	}

	// Load the door sprite sheet
	if(!textureManager::Instance()->load("./img/tiledMap/door.PNG", "door", renderer)) {
		MessageBox(NULL,"Can not load image file", "error", MB_OK);
		return false;
	}

	// Load the stairs sprite sheet
	if(!textureManager::Instance()->load("./img/tiledMap/up_floor.PNG", "up", renderer)) {
		MessageBox(NULL,"Can not load image file", "error", MB_OK);
		return false;
	}
	if(!textureManager::Instance()->load("./img/tiledMap/down_floor.PNG", "down", renderer)) {
		MessageBox(NULL,"Can not load image file", "error", MB_OK);
		return false;
	}

	// Initialize Object Factory
	GameObjectFactory::Instance();

	// Initialize Collision detector
	Collision::Instance();

	// Initialize Object Fatory's Creator function
	// Enemy
	BaseCreator* enemyCreator = new EnemyCreator();
	GameObjectFactory::Instance()->registerType("enemy",enemyCreator);
	// Map
	BaseCreator* mapCreator = new TileCreator();
	GameObjectFactory::Instance()->registerType("map", mapCreator);
	// Medicine
	BaseCreator* medicineCreator = new MedicineCreator(); 
	GameObjectFactory::Instance()->registerType("medicine", medicineCreator);
	// Jewel
	BaseCreator* jewelCreator = new JewelCreator();
	GameObjectFactory::Instance()->registerType("jewel", jewelCreator);
	// Key
	BaseCreator* keyCreator = new KeyCreator(); 
	GameObjectFactory::Instance()->registerType("key", keyCreator);
	// Door
	BaseCreator* doorCreator = new DoorCreator(); 
	GameObjectFactory::Instance()->registerType("door", doorCreator);
	// Weapon
	BaseCreator* weaponCreator = new WeaponCreator(); // Door
	GameObjectFactory::Instance()->registerType("weapon", weaponCreator);
	// Stair
	BaseCreator* stairCreator = new StairCreator();
	GameObjectFactory::Instance()->registerType("stair", stairCreator);

	// Initialize floor 
	Floor* Floor1 = new Floor();
	Floor* Floor2 = new Floor();

	// Start parsing XML file
	std::string temp[] = {"Enemy","Medicine","Weapon","Jewel", "Key", "Door", "Stair", "Map" };
	size_t len = sizeof(temp) / sizeof(temp[0]);
	
    // Floor1
	for(size_t i = 0; i < len; i++) {
		Parser::parseState("./data/Floor1.xml", temp[i], Floor1->elements, Floor1->map);
	}

	// Floor2
	for(size_t i = 0; i < len; i++) {
		Parser::parseState("./data/Floor2.xml", temp[i], Floor2->elements, Floor2->map);
	}

	// Assign 
	// floors is a map(not array)
	floors[1] = Floor1;
	floors[2] = Floor2;

	// Current Floor 
	currentFloor = 1;

	// Get background info
	Parser::parseState("./data/Floor1.xml","Background",nullptr, &background);


	// Initialiae the player
	LoaderParams* param = new LoaderParams(11*32,10*32,32,32,0,0,"hero");
	player = new Player();
	player->load(param);
	delete param;

	return true;
}


void Game::render() {
	// Always make sure screen got cleared first
	SDL_RenderClear(renderer);

	// Render background
	for(std::vector<std::vector<SDLGameObject*> >::iterator i = background.begin(); i != background.end(); ++i) {
		for(std::vector<SDLGameObject*>::iterator j = (*i).begin(); j != (*i).end(); ++j) {
			(*j)->draw();
		}
	}
	// Render the entire floor
	floors[currentFloor]->render();

	// Render player
	player->draw();

	// Render the status of the player
	textureManager::Instance()->drawStatus("hero","item",player,renderer,font);

	// Present!
	SDL_RenderPresent(renderer);
}


void Game::clean() {
    // Delete the whole SDL window and renderer (think of it as a brush to paint :) )
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	// Delete background
	for(std::vector<std::vector<SDLGameObject*> >::iterator i = background.begin(); i != background.end(); ++i) {
		for(std::vector<SDLGameObject*>::iterator j = (*i).begin(); j != (*i).end(); ++j) {
			delete(*j);
		}
	}
	// Clean up floors
	for(std::map<int, Floor*>::iterator i = floors.begin(); i != floors.end(); i++) {
		delete i->second;
	}

	// Need to make sure TTF got quit to prevent any memory leak here
	TTF_CloseFont(font);
	TTF_Quit();

	// Delete singletons !
	delete GameObjectFactory::Instance();
	delete textureManager::Instance();
	delete Collision::Instance();
	delete instance;

	// At last, quit SDL
	SDL_Quit();
}


void Game::update(){
	// Only need to update the elements.
	std::unordered_map<Position*, SDLGameObject*, PositionHash>::iterator i;
	std::unordered_map<Position*, SDLGameObject*, PositionHash>* floor = &(floors[currentFloor]->elements);
	for(i = floor->begin(); i != floor->end(); ++i) {
		if(i->second != nullptr) {
			i->second->update();
		}
	}
}


void Game::handleEvents(){ 
	SDL_Event Event;
	// Events are waiting in a queue! 
	if(SDL_PollEvent(&Event)){
		if(Event.type == SDL_QUIT) {
			Running = false;
		}
		else if(Event.type == SDL_KEYDOWN) {
			switch(Event.key.keysym.sym) { // Get the key type
			// If press up 
			case SDLK_UP :
				// Reset frames to make player face up
				player->setRow(3);
				player->setFrame(0);
				// If we have wall in the north...
				if(!Collision::Instance()->detectWall(&(floors[currentFloor]->map),player,'N',32)) {
					break;
				}
				Position p(player->getX() / 32, player->getY() / 32 - 1);
				if(floors[currentFloor]->elements.find(p) != floors[currentFloor]->elements.end()) {
					floors[currentFloor]->elements[p]->collide(player);
				}
				else {
					if(player->getY() >= 64) player->decreaseY();
				}
				break;
			case SDLK_DOWN:
				// Reset frames to make player face down
				player->setRow(0);
				player->setFrame(0);
				// If we have wall in the north...
				if(!Collision::Instance()->detectWall(&(floors[currentFloor]->map),player,'N',32)) {
					break;
				}
				Position p(player->getX() / 32, player->getY() / 32 + 1);
				if(floors[currentFloor]->elements.find(p) != floors[currentFloor]->elements.end()) {
					floors[currentFloor]->elements[p]->collide(player);
				}
				else {
					if(player->getY() <= 320) player->increaseY();
				}
				break;
			case SDLK_LEFT:
				// Reset frames to make player face left
				player->setRow(1);
				player->setFrame(0);
				// If we have wall in the north...
				if(!Collision::Instance()->detectWall(&(floors[currentFloor]->map),player,'N',32)) {
					break;
				}
				Position p(player->getX() / 32 - 1, player->getY() / 32);
				if(floors[currentFloor]->elements.find(p) != floors[currentFloor]->elements.end()) {
					floors[currentFloor]->elements[p]->collide(player);
				}
				else {
					if(player->getX() >= 224) player->decreaseX();
				}
				break;
			case SDLK_RIGHT:
				// Reset frames to make player face right
				player->setRow(2);
				player->setFrame(0);
				// If we have wall in the north...
				if(!Collision::Instance()->detectWall(&(floors[currentFloor]->map),player,'N',32)) {
					break;
				}
				Position p(player->getX() / 32 + 1, player->getY() / 32 - 1);
				if(floors[currentFloor]->elements.find(p) != floors[currentFloor]->elements.end()) {
					floors[currentFloor]->elements[p]->collide(player);
				}
				else {
					if(player->getX() <= 480) player->increaseX();
				}
				break;
			}
		}
		else if(Event.type == SDL_KEYUP) { // Key released. Make sure the player is facing at the correct direction
			switch(Event.key.keysym.sym) { 
			case SDLK_UP :
				player->setRow(3);
				player->setFrame(0);
				break;
			case SDLK_DOWN:
				player->setRow(0);
				player->setFrame(0);
				break;
			case SDLK_LEFT:
				player->setRow(1);
				player->setFrame(0);
				break;
			case SDLK_RIGHT:
				player->setRow(2);
				player->setFrame(0);
				break;
			}
		}
		else {}
   }
}

// Check in main if game is still running
bool Game::running() { return Running;}

void Game::gameover() { Running = false;}

// This is useful while rendering in other places e.g textureManager
SDL_Renderer* Game::getRenderer(){
	return renderer;
}

Floor* Game::getCurrentFloor(){
	return floors[currentFloor];
}

TTF_Font* Game::getFont() {
	return font;
}

void Game::increaseFloor() {
	 ++currentFloor;
}

void Game::decreaseFloor() {
	--currentFloor;
}

int Game::floorNumber() {
	return currentFloor;
}