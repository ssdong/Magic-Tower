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

	// TODO; This part needs optimization
	// Initialize floor 
	Floor* Floor1 = new Floor();
	Floor* Floor2 = new Floor();
	Floor* Floor3 = new Floor();
	Floor* Floor4 = new Floor();
	Floor* Floor5 = new Floor();

	// Start parsing XML file
	// Floor1
	Parser::parseState("./data/Floor1.xml","Enemy",&Floor1->enemies, nullptr);
	Parser::parseState("./data/Floor1.xml","Medicine",&Floor1->medicines, nullptr); 
	Parser::parseState("./data/Floor1.xml","Weapon",&Floor1->weapons,nullptr);
	Parser::parseState("./data/Floor1.xml","Jewel",&Floor1->jewels, nullptr); 
	Parser::parseState("./data/Floor1.xml","Key",&Floor1->keys, nullptr); 
	Parser::parseState("./data/Floor1.xml","Door",&Floor1->doors, nullptr);
	Parser::parseState("./data/Floor1.xml","Stair",&Floor1->stairs, nullptr);
	Parser::parseState("./data/Floor1.xml","Map",nullptr, &Floor1->map);

	// Floor2
	Parser::parseState("./data/Floor2.xml","Enemy",&Floor2->enemies, nullptr);
	Parser::parseState("./data/Floor2.xml","Medicine",&Floor2->medicines, nullptr); 
	Parser::parseState("./data/Floor2.xml","Weapon",&Floor2->weapons,nullptr);
	Parser::parseState("./data/Floor2.xml","Jewel",&Floor2->jewels, nullptr); 
	Parser::parseState("./data/Floor2.xml","Door",&Floor2->doors, nullptr);
	Parser::parseState("./data/Floor2.xml","Stair",&Floor2->stairs, nullptr);
	Parser::parseState("./data/Floor2.xml","Map",nullptr, &Floor2->map);

	// Floor3
	Parser::parseState("./data/Floor3.xml","Enemy",&Floor3->enemies, nullptr);
	Parser::parseState("./data/Floor3.xml","Medicine",&Floor3->medicines, nullptr); 
	Parser::parseState("./data/Floor3.xml","Weapon",&Floor3->weapons,nullptr);
	Parser::parseState("./data/Floor3.xml","Jewel",&Floor3->jewels, nullptr); 
	Parser::parseState("./data/Floor3.xml","Door",&Floor3->doors, nullptr);
	Parser::parseState("./data/Floor3.xml","Stair",&Floor3->stairs, nullptr);
	Parser::parseState("./data/Floor3.xml","Map",nullptr, &Floor3->map);

	// Floor4
	Parser::parseState("./data/Floor4.xml","Enemy",&Floor4->enemies, nullptr);
	Parser::parseState("./data/Floor4.xml","Medicine",&Floor4->medicines, nullptr); 
	Parser::parseState("./data/Floor4.xml","Weapon",&Floor4->weapons,nullptr);
	Parser::parseState("./data/Floor4.xml","Jewel",&Floor4->jewels, nullptr); 
	Parser::parseState("./data/Floor4.xml","Door",&Floor4->doors, nullptr);
	Parser::parseState("./data/Floor4.xml","Stair",&Floor4->stairs, nullptr);
	Parser::parseState("./data/Floor4.xml","Map",nullptr, &Floor4->map);

	// Floor5
	Parser::parseState("./data/Floor5.xml","Enemy",&Floor5->enemies, nullptr);
	Parser::parseState("./data/Floor5.xml","Medicine",&Floor5->medicines, nullptr); 
	Parser::parseState("./data/Floor5.xml","Weapon",&Floor5->weapons,nullptr);
	Parser::parseState("./data/Floor5.xml","Jewel",&Floor5->jewels, nullptr); 
	Parser::parseState("./data/Floor5.xml","Door",&Floor5->doors, nullptr);
	Parser::parseState("./data/Floor5.xml","Stair",&Floor5->stairs, nullptr);
	Parser::parseState("./data/Floor5.xml","Map",nullptr, &Floor5->map);

	// Assign 
	// floors is a map(not array)
	floors[1] = Floor1;
	floors[2] = Floor2;
	floors[3] = Floor3;
	floors[4] = Floor4;
	floors[5] = Floor5;

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
	for(std::vector<SDLGameObject*>::iterator i = floors[currentFloor]->enemies.begin(); i != floors[currentFloor]->enemies.end(); ++i) {
		if((*i) != nullptr) {
		  (*i)->update();
		}
	}
}


/* This handler is probably used better in larger maps. No need to store every position's info. 
   Think of having a 1000 x 1000 map... Right now it is only catching user's up, left, down, right 
   keys and it will automatically detect collisions(pick up items, go upstairs or downstairs) and 
   make sure player not dead when fight against enemies. 
   TODO; Possible optimization. Calculate player position once and store
   */
void Game::handleEvents(){ 
	SDL_Event Event;
	// Events are waiting in a queue! 
	if(SDL_PollEvent(&Event)){
		if(Event.type == SDL_QUIT) {
			Running = false;
		}
		else if(Event.type == SDL_KEYDOWN) {
			int position;
			char stairType;
			switch(Event.key.keysym.sym) { // Get the key type
			// If press up 
			case SDLK_UP :
				// Reset frames to make player face up
				player->setRow(3);
				player->setFrame(0);
				/*
				    Possible optimizations should be considered here. What if more and more elements are added?
					Can we avoid storing position information or use less memory when large maps are used? 
				*/
				// If we have a key in the north...
				if(Collision::Instance()->detectKey(&(floors[currentFloor]->keys),player,'N',32,position) == false) {
					// If we have a jewel in the north...
				   if(Collision::Instance()->detectJewel(&(floors[currentFloor]->jewels),player,'N',32,position) == false) {
					   // If we have a medicine in the north...
					   if(Collision::Instance()->detectMedicine(&(floors[currentFloor]->medicines),player,'N',32,position) == false) {
						   // If we have a door in the north...
						   if(Collision::Instance()->detectDoorExist(&(floors[currentFloor]->doors),player,'N',32,position) == false) {
							   // If we have an enemy in the north...
							   if(Collision::Instance()->detectEnemyExist(&(floors[currentFloor]->enemies),player,'N',32,position) == false) {
								   // If we have wall in the north...
								  if(Collision::Instance()->detectWall(&(floors[currentFloor]->map),player,'N',32) == false) {
									  // If we have stairs in the north...
									  if(Collision::Instance()->detectStair(&(floors[currentFloor]->stairs), player, 'N',32,stairType) == false) {
									    if(player->getY() >= 64) {
                                            player->decreaseY();
									    }
									  }
									  else {
										  if(stairType == 'U'){ // If trying to get upstairs
										     ++currentFloor;
										     // Set Player coordinate
											 std::vector<SDLGameObject*>::iterator i;
										     for(i = floors[currentFloor]->stairs.begin(); i != floors[currentFloor]->stairs.end(); i++) {
											     if(dynamic_cast<Stair*>(*i)->type == 'D') {
												     dynamic_cast<Player*>(player)->setX((*i)->getX());
												     dynamic_cast<Player*>(player)->setY((*i)->getY());
											     }
										     }
											 textureManager::Instance()->changeFloor(renderer,font,currentFloor);
										  }
										  else {
											--currentFloor;
											// Set Player coordinate
											std::vector<SDLGameObject*>::iterator i ;
											for(i = floors[currentFloor]->stairs.begin(); i != floors[currentFloor]->stairs.end(); i++) {
											     if(dynamic_cast<Stair*>(*i)->type == 'U') {
												     dynamic_cast<Player*>(player)->setX((*i)->getX());
												     dynamic_cast<Player*>(player)->setY((*i)->getY());
											     }
										     }
											textureManager::Instance()->changeFloor(renderer,font,currentFloor);
										  }
									  }
								  }
							   }
							   else {  // Now an enemy exists....  
								   if(Collision::Instance()->detectCanFightWithEnemy(&(floors[currentFloor]->enemies),player,'N',32,position) == false) {
									   // Unable to defeat...
							       }
								   else {
									   // Yes! Can defeat!
									   int PlayerHP = dynamic_cast<Player*>(player)->getHP();
	                                   int EnemyHP = dynamic_cast<Enemy*>((floors[currentFloor]->enemies)[position])->getHP();

									   // Calculate player to enemy's damage and vice versa
		                               int P_E_damage = (100.0 / (100 + dynamic_cast<Enemy*>((floors[currentFloor]->enemies)[position])->getDefence())) * dynamic_cast<Player*>(player)->getAttack();
		                               int E_P_damage = (100.0 / (100 + dynamic_cast<Player*>(player)->getDefence())) * dynamic_cast<Enemy*>((floors[currentFloor]->enemies)[position])->getAttack();

									   // Start fighting!
									   unsigned int lastTime = SDL_GetTicks();
									   while(true) {
										   if(Collision::Instance()->fight( &(floors[currentFloor]->enemies),
											                                player,'N',32,position,
																			renderer,font,PlayerHP,
																			EnemyHP,P_E_damage,
																			E_P_damage,lastTime ) == true) {
											   // Print the winning message
											   textureManager::Instance()->drawMessage( "win",position, 
												                                        &(floors[currentFloor]->enemies),
																						renderer,&background,
																						floors[currentFloor],
																						player,font );
											   // Rest player status
											   dynamic_cast<Player*>(player)->setHP(PlayerHP - dynamic_cast<Player*>(player)->getHP());
											   dynamic_cast<Player*>(player)->setGold(dynamic_cast<Enemy*>(floors[currentFloor]->enemies[position])->getGold());
											   dynamic_cast<Player*>(player)->setExperience(dynamic_cast<Enemy*>(floors[currentFloor]->enemies[position])->getExperience());
											   delete (floors[currentFloor]->enemies)[position];
											   (floors[currentFloor]->enemies)[position] = nullptr;
											   break;
										   }
										   else {
											   // Print the fighting message
                                               textureManager::Instance()->drawMessage( "fight",position,
												                                        &(floors[currentFloor]->enemies),
																						renderer,&background,
																						floors[currentFloor],
																						player,font,PlayerHP,EnemyHP );
										   }
									   }
								   }
							   }
						   }
						   else { // Now we have a door at front...
							   while(!Collision::Instance()->detectDoor(&(floors[currentFloor]->doors),player,'N',32,position)) {
								   render();
							   }
							   render();
						   }
					   }
					   else { // Now we have a medicine at front...
						   textureManager::Instance()->drawMessage( "medicine",position,
							                                        &(floors[currentFloor]->medicines),
																	renderer,&background,
																	floors[currentFloor],
																	player,font );
						   // Print Medicine message here
					   }
				   }
				   else {  // Now we have a jewel at front...
					   textureManager::Instance()->drawMessage( "jewel",position,
						                                        &(floors[currentFloor]->jewels),
																renderer,&background,
																floors[currentFloor],
																player,font );
					   // Print Jewel message here
				   }
				}
				else { // Now we have a key at front...
					textureManager::Instance()->drawMessage( "key",position,
						                                     &(floors[currentFloor]->keys),
															 renderer,&background,
															 floors[currentFloor],
															 player,font );
					// Print Key message here
				}
				break;
			case SDLK_DOWN:
				// Reset frames to make player face down
				player->setRow(0);
				player->setFrame(0);
				// If we have a key in the south...
				if(Collision::Instance()->detectKey(&(floors[currentFloor]->keys), player,'S',32,position) == false) {
					// If we have a jewel in the south...
				   if(Collision::Instance()->detectJewel(&(floors[currentFloor]->jewels),player,'S',32,position) == false) {
					   // If we have a medicine in the south...
					   if(Collision::Instance()->detectMedicine(&(floors[currentFloor]->medicines),player,'S',32,position) == false) {
						   // If we have a door in the south...
						   if(Collision::Instance()->detectDoorExist(&(floors[currentFloor]->doors),player,'S',32,position) == false) {
							   // If we have an enemy in the south...
							   if(Collision::Instance()->detectEnemyExist(&(floors[currentFloor]->enemies),player,'S',32,position) == false) {
								   // If we have wall in the south...
								   if(Collision::Instance()->detectWall(&(floors[currentFloor]->map),player,'S',32) == false) {
									   // If we have stairs in the south...
									   if(Collision::Instance()->detectStair(&(floors[currentFloor]->stairs), player, 'S',32,stairType) == false) {
									     if(player->getY() <= 320) {
				                            player->increaseY();
									     }
									   }
									   else {
										   if(stairType == 'U'){ // If trying to get upstairs
										     ++currentFloor;
										     // Set Player coordinate
											 std::vector<SDLGameObject*>::iterator i;
										     for( i = floors[currentFloor]->stairs.begin(); i != floors[currentFloor]->stairs.end(); i++) {
											     if(dynamic_cast<Stair*>(*i)->type == 'D') {
												     dynamic_cast<Player*>(player)->setX((*i)->getX());
												     dynamic_cast<Player*>(player)->setY((*i)->getY());
											     }
										     }
											 textureManager::Instance()->changeFloor(renderer,font,currentFloor);
										  }
										  else { // Downstairs..
											--currentFloor;
											std::vector<SDLGameObject*>::iterator i;
											for( i= floors[currentFloor]->stairs.begin(); i != floors[currentFloor]->stairs.end(); i++) {
											     if(dynamic_cast<Stair*>(*i)->type == 'U') {
												     dynamic_cast<Player*>(player)->setX((*i)->getX());
												     dynamic_cast<Player*>(player)->setY((*i)->getY());
											     }
										     }
											textureManager::Instance()->changeFloor(renderer,font,currentFloor);
										  }
									   }
								   }
							   }
							   else { // Caculate if we can defeat the enemy
								   if(Collision::Instance()->detectCanFightWithEnemy(&(floors[currentFloor]->enemies),player,'S',32,position) == false) {
									    // Unable to defeat...
								    }
								   else { 
									   // Yes! Can defeat!
									   int PlayerHP = dynamic_cast<Player*>(player)->getHP();
	                                   int EnemyHP = dynamic_cast<Enemy*>((floors[currentFloor]->enemies)[position])->getHP();

									   // Calculate player to enemy's damage and vice versa
		                               int P_E_damage = (100.0 / (100 + dynamic_cast<Enemy*>((floors[currentFloor]->enemies)[position])->getDefence())) * dynamic_cast<Player*>(player)->getAttack();
		                               int E_P_damage = (100.0 / (100 + dynamic_cast<Player*>(player)->getDefence())) * dynamic_cast<Enemy*>((floors[currentFloor]->enemies)[position])->getAttack();

									   // Start fighting!
									   unsigned int lastTime = SDL_GetTicks();
									   while(true) {
										   if(Collision::Instance()->fight( &(floors[currentFloor]->enemies),
											                                player,'S',32,position,
																			renderer,font,PlayerHP,
																			EnemyHP,P_E_damage,
																			E_P_damage,lastTime ) == true) {
											   // Print the winning message
                                               textureManager::Instance()->drawMessage( "win",position,
												                                        &(floors[currentFloor]->enemies),
																						renderer,&background,
																						floors[currentFloor],
																						player,font );
											   // Rest player status
											   dynamic_cast<Player*>(player)->setHP(PlayerHP - dynamic_cast<Player*>(player)->getHP());
											   dynamic_cast<Player*>(player)->setGold(dynamic_cast<Enemy*>(floors[currentFloor]->enemies[position])->getGold());
											   dynamic_cast<Player*>(player)->setExperience(dynamic_cast<Enemy*>(floors[currentFloor]->enemies[position])->getExperience());
											   delete (floors[currentFloor]->enemies[position]);
											   floors[currentFloor]->enemies[position] = nullptr;
											   break;
										   }
										   else {
											   // Print the fighting message
                                               textureManager::Instance()->drawMessage( "fight",position,
												                                        &(floors[currentFloor]->enemies),
																						renderer,&background,
																						floors[currentFloor],
																						player,font,
																						PlayerHP,EnemyHP );
										   }
									   }
								   }
							   }
						   }
						   else { // Now we have a door at front...
							   while(!Collision::Instance()->detectDoor(&(floors[currentFloor]->doors),player,'S',32,position)) {
								   render();
							   }
							   render();
						   }
					   }
					   else  { // Now we have a medicine at front...
						   // Print Medicine message here
						   textureManager::Instance()->drawMessage( "medicine",position,
							                                        &(floors[currentFloor]->medicines),
																	renderer,&background,
																	floors[currentFloor],
																	player,font);
					   }
				   }
				   else { // Now we have a jewel at front...
					   // Print Jewel message here
					   textureManager::Instance()->drawMessage( "jewel",position,
						                                        &(floors[currentFloor]->jewels),
																renderer,&background,
																floors[currentFloor],
																player,font );
				   }
				}
				else { // Now we have a key at front...
					// Print Key message here
					textureManager::Instance()->drawMessage( "key",position,
						                                     &(floors[currentFloor]->keys),
															 renderer,&background,
															 floors[currentFloor],
															 player,font );
				}
				break;
			case SDLK_LEFT:
				// Reset frames to make player face left
				player->setRow(1);
				player->setFrame(0);
				// If we have a key in the west...
				if(Collision::Instance()->detectKey( &(floors[currentFloor]->keys), player,'W',32,position) == false) {
					// If we have a jewel in the west...
				   if(Collision::Instance()->detectJewel(&(floors[currentFloor]->jewels),player,'W',32,position) == false) {
					   // If we have a medicine in the west...
					   if(Collision::Instance()->detectMedicine(&(floors[currentFloor]->medicines),player,'W',32,position) == false) {
						   // If we have a door in the west...
						   if(Collision::Instance()->detectDoorExist(&(floors[currentFloor]->doors),player,'W',32,position) == false) {
							   // If we have a enemy in the west...
							   if(Collision::Instance()->detectEnemyExist(&(floors[currentFloor]->enemies),player,'W',32,position) == false) {
								   // If we have wall in the west...
								   if(Collision::Instance()->detectWall(&(floors[currentFloor]->map),player,'W',32) == false) {
									   // If we have stairs in the west...
									   if(Collision::Instance()->detectStair(&(floors[currentFloor]->stairs), player, 'W',32,stairType) == false) {
									     if(player->getX() >= 224) {
				                            player->decreaseX();
									     }
									   }
									   else {
										  if(stairType == 'U'){ // If trying to get upstairs
										     ++currentFloor;
										     // Set Player coordinate
											 std::vector<SDLGameObject*>::iterator i;
										     for(i = floors[currentFloor]->stairs.begin(); i != floors[currentFloor]->stairs.end(); i++) {
											     if(dynamic_cast<Stair*>(*i)->type == 'D') {
												     dynamic_cast<Player*>(player)->setX((*i)->getX());
												     dynamic_cast<Player*>(player)->setY((*i)->getY());
											     }
										     }
											 textureManager::Instance()->changeFloor(renderer,font,currentFloor);
										  }
										  else { // Downstairs
											--currentFloor;
											std::vector<SDLGameObject*>::iterator i;
											for(i = floors[currentFloor]->stairs.begin(); i != floors[currentFloor]->stairs.end(); i++) {
											     if(dynamic_cast<Stair*>(*i)->type == 'U') {
												     dynamic_cast<Player*>(player)->setX((*i)->getX());
												     dynamic_cast<Player*>(player)->setY((*i)->getY());
											     }
										     }
											textureManager::Instance()->changeFloor(renderer,font,currentFloor);
										  }
									   }
								   }
							   }
							   else { // Caculate if we can defeat the enemy
								   if(Collision::Instance()->detectCanFightWithEnemy(&(floors[currentFloor]->enemies),player,'W',32,position) == false) {
									   // Unable to defeat
								   }
								   else {
									   // Yes! Can defeat!
									   int PlayerHP = dynamic_cast<Player*>(player)->getHP();
	                                   int EnemyHP = dynamic_cast<Enemy*>((floors[currentFloor]->enemies)[position])->getHP();

									   // Calculate player to enemy's damage and vice versa
		                               int P_E_damage = (100.0 / (100 + dynamic_cast<Enemy*>((floors[currentFloor]->enemies)[position])->getDefence())) * dynamic_cast<Player*>(player)->getAttack();
		                               int E_P_damage = (100.0 / (100 + dynamic_cast<Player*>(player)->getDefence())) * dynamic_cast<Enemy*>((floors[currentFloor]->enemies)[position])->getAttack();

									   // Start fighting!
									   unsigned int lastTime = SDL_GetTicks();
									   while(true) {
										   if(Collision::Instance()->fight( &(floors[currentFloor]->enemies),
											                                player,'W',32,position,
																			renderer,font,PlayerHP,
																			EnemyHP,P_E_damage,
																			E_P_damage,lastTime ) == true) {
											   // Print the winning message
                                               textureManager::Instance()->drawMessage( "win",position,
												                                        &(floors[currentFloor]->enemies),
																					    renderer,&background,
																						floors[currentFloor],
																					    player,font );
											   // Rest player status
											   dynamic_cast<Player*>(player)->setHP(PlayerHP - dynamic_cast<Player*>(player)->getHP());
											   dynamic_cast<Player*>(player)->setGold(dynamic_cast<Enemy*>(floors[currentFloor]->enemies[position])->getGold());
											   dynamic_cast<Player*>(player)->setExperience(dynamic_cast<Enemy*>(floors[currentFloor]->enemies[position])->getExperience());
											   delete (floors[currentFloor]->enemies[position]);
											   floors[currentFloor]->enemies[position] = nullptr;
											   break;
										   }
										   else {
											   // Print the fighting message
                                               textureManager::Instance()->drawMessage( "fight",position,
												                                        &(floors[currentFloor]->enemies),
																					    renderer,&background,
																						floors[currentFloor],
																					    player,font,PlayerHP,EnemyHP );
										   }
									   }
								   }
							   }
						   }
						   else { // Now we have a door at front...
							   while(!Collision::Instance()->detectDoor(&(floors[currentFloor]->doors),player,'W',32,position)) {
								   render();
							   }
							   render();
						   }
					   }
					   else { // Now we have a medicine at front...
						   // Print Medicine Message here
						   textureManager::Instance()->drawMessage( "medicine",position,
							                                        &(floors[currentFloor]->medicines),
																    renderer,&background,
																	floors[currentFloor],
																    player,font );
					   }
				   }
				   else { // Now we have a jewel at front...
					   // Print Jewel Message here
					   textureManager::Instance()->drawMessage( "jewel",position,
						                                        &(floors[currentFloor]->jewels),
															    renderer,&background,
																floors[currentFloor],
															    player,font );
				   }
				}
				else { // Now we have a key at front...
					// Print Key Message here
					textureManager::Instance()->drawMessage( "key",position,
						                                     &(floors[currentFloor]->keys),
															 renderer,&background,
															 floors[currentFloor],
															 player,font );
				}
				break;
			case SDLK_RIGHT:
				// Reset frames to make player face right
				player->setRow(2);
				player->setFrame(0);
				// If we have a key in the east...
				if(Collision::Instance()->detectKey(&(floors[currentFloor]->keys), player,'E',32,position) == false) {
					// If we have a jewel in the east...
				   if(Collision::Instance()->detectJewel(&(floors[currentFloor]->jewels),player,'E',32,position) == false) {
					   // If we have a medicine in the east...
					   if(Collision::Instance()->detectMedicine(&(floors[currentFloor]->medicines),player,'E',32,position) == false) {
						   // If we have a door in the east...
						   if(Collision::Instance()->detectDoorExist(&(floors[currentFloor]->doors),player,'E',32,position) == false) {
							   // If we have an enemy in the east...
							   if(Collision::Instance()->detectEnemyExist(&(floors[currentFloor]->enemies),player,'E',32,position) == false) {
								   // If we have wall in the east...
								   if(Collision::Instance()->detectWall(&(floors[currentFloor]->map),player,'E',32) == false) {
									   // If we have stairs in the east...
									   if(Collision::Instance()->detectStair(&(floors[currentFloor]->stairs), player, 'E',32,stairType) == false) {
									     if(player->getX() <= 480) {
				                            player->increaseX();
									     }
									   }
									   else {
										  if(stairType == 'U'){ // If trying to go upstairs...
										     ++currentFloor;
										     // Set Player coordinate
											 std::vector<SDLGameObject*>::iterator i;
										     for(i = floors[currentFloor]->stairs.begin(); i != floors[currentFloor]->stairs.end(); i++) {
											     if(dynamic_cast<Stair*>(*i)->type == 'D') {
												     dynamic_cast<Player*>(player)->setX((*i)->getX());
												     dynamic_cast<Player*>(player)->setY((*i)->getY());
											     }
										     }
											 textureManager::Instance()->changeFloor(renderer,font,currentFloor);
										  }
										  else { // Downstairs
											--currentFloor;
											std::vector<SDLGameObject*>::iterator i;
											for(i = floors[currentFloor]->stairs.begin(); i != floors[currentFloor]->stairs.end(); i++) {
											     if(dynamic_cast<Stair*>(*i)->type == 'U') {
												     dynamic_cast<Player*>(player)->setX((*i)->getX());
												     dynamic_cast<Player*>(player)->setY((*i)->getY());
											     }
										     }
											 textureManager::Instance()->changeFloor(renderer,font,currentFloor);
										  }
									   }
								   }
							   }
							   else { // Calculate if we can defeat the enemy
								   if(Collision::Instance()->detectCanFightWithEnemy(&(floors[currentFloor]->enemies),player,'E',32,position) == false) {
									   // Unable to defeat
								   }
								   else {
									   // Yes! Can defeat!
									   int PlayerHP = dynamic_cast<Player*>(player)->getHP();
	                                   int EnemyHP = dynamic_cast<Enemy*>((floors[currentFloor]->enemies)[position])->getHP();

									   // Calculate player to enemy's damage and vice versa
		                               int P_E_damage = (100.0 / (100 + dynamic_cast<Enemy*>((floors[currentFloor]->enemies)[position])->getDefence())) * dynamic_cast<Player*>(player)->getAttack();
		                               int E_P_damage = (100.0 / (100 + dynamic_cast<Player*>(player)->getDefence())) * dynamic_cast<Enemy*>((floors[currentFloor]->enemies)[position])->getAttack();

									   // Start fighting!
									   unsigned int lastTime = SDL_GetTicks();
									   while(true) {
										   if(Collision::Instance()->fight( &(floors[currentFloor]->enemies),
											                                player,'E',32,position,
																			renderer,font,PlayerHP,
																		    EnemyHP,P_E_damage,
																			E_P_damage,lastTime ) == true) {
											   // Print the winning message
                                               textureManager::Instance()->drawMessage( "win",position,
												                                        &(floors[currentFloor]->enemies),
																					    renderer,&background,
																						floors[currentFloor],
																					    player,font );
											   // Rest player status
											   dynamic_cast<Player*>(player)->setHP(PlayerHP - dynamic_cast<Player*>(player)->getHP());
											   dynamic_cast<Player*>(player)->setGold(dynamic_cast<Enemy*>(floors[currentFloor]->enemies[position])->getGold());
											   dynamic_cast<Player*>(player)->setExperience(dynamic_cast<Enemy*>(floors[currentFloor]->enemies[position])->getExperience());
											   delete (floors[currentFloor]->enemies[position]);
											   floors[currentFloor]->enemies[position] = nullptr;
											   break;
										   }
										   else {
											   // Print the fighting message
                                               textureManager::Instance()->drawMessage( "fight",position,
												                                        &(floors[currentFloor]->enemies),
																					    renderer,&background,
																						floors[currentFloor],
																					    player,font,PlayerHP,EnemyHP );
										   }
									   }
								   }
							   }
						   }
						   else { // Now we have a door at front..
							   while(!Collision::Instance()->detectDoor(&(floors[currentFloor]->doors),player,'E',32,position)) {
								   render();
							   }
							   render();
						   }
					   }
					   else {  // Now we have a medicine at front..
						   // Print Medicine message here
						   textureManager::Instance()->drawMessage( "medicine",position,
							                                        &(floors[currentFloor]->medicines),
							                                        renderer,&background,
																    floors[currentFloor],
																	player,font );
					   }
				   }
				   else {  // Now we have a jewel at front..
					   // Print Jewel message here
					   textureManager::Instance()->drawMessage( "jewel",position,
						                                        &(floors[currentFloor]->jewels),
															    renderer,&background,
															    floors[currentFloor],
																player,font );
				   }
				}
				else { // Now we have a key at front..
					// Print Key message here
					textureManager::Instance()->drawMessage( "key",position,
						                                     &(floors[currentFloor]->keys),
															 renderer,&background,
															 floors[currentFloor],
															 player,font );
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
SDL_Renderer* Game::getRenderer() const{
	return renderer;
}