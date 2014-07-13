/* 
   Game.cpp and Game.h

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

	// Initialize floor
	Floor* Floor1 = new Floor();
	Floor* Floor2 = new Floor();

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
	BaseCreator* enemyCreator = new EnemyCreator();  // Enemy
	GameObjectFactory::Instance()->registerType("enemy",enemyCreator);
	BaseCreator* mapCreator = new TileCreator(); // Map
	GameObjectFactory::Instance()->registerType("map", mapCreator);
	BaseCreator* medicineCreator = new MedicineCreator(); // Medicine
	GameObjectFactory::Instance()->registerType("medicine", medicineCreator);
	BaseCreator* jewelCreator = new JewelCreator(); // Jewel
	GameObjectFactory::Instance()->registerType("jewel", jewelCreator);
	BaseCreator* keyCreator = new KeyCreator(); // Key
	GameObjectFactory::Instance()->registerType("key", keyCreator);
	BaseCreator* doorCreator = new DoorCreator(); // Door
	GameObjectFactory::Instance()->registerType("door", doorCreator);
	BaseCreator* weaponCreator = new WeaponCreator(); // Door
	GameObjectFactory::Instance()->registerType("weapon", weaponCreator);
	BaseCreator* stairCreator = new StairCreator(); // Stair
	GameObjectFactory::Instance()->registerType("stair", stairCreator);

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

	// Assign 
	floors[1] = Floor1;
	floors[2] = Floor2;

	// Current Floor 
	currentFloor = 1;

	Parser::parseState("./data/Floor1.xml","Background",nullptr, &background);


	// initialiae the player
	LoaderParams* param = new LoaderParams(11*32,10*32,32,32,0,0,"hero");
	player = new Player();
	player->load(param);
	delete param;

	return true;
}
void Game::render() {
	SDL_RenderClear(renderer);

	// Render background
	for(std::vector<std::vector<SDLGameObject*> >::iterator i = background.begin(); i != background.end(); ++i) {
		for(std::vector<SDLGameObject*>::iterator j = (*i).begin(); j != (*i).end(); ++j) {
			(*j)->draw();
		}
	}
	// Render Floor
	floors[currentFloor]->render();
	// Render player
	player->draw();

	// Render the status of the player
	textureManager::Instance()->drawStatus("hero","item",player,renderer,font);

	// Clean up
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	// Delete background
	for(std::vector<std::vector<SDLGameObject*> >::iterator i = background.begin(); i != background.end(); ++i) {
		for(std::vector<SDLGameObject*>::iterator j = (*i).begin(); j != (*i).end(); ++j) {
			delete(*j);
		}
	}
	// Clean up Map
	for(std::map<int, Floor*>::iterator i = floors.begin(); i != floors.end(); i++) {
		delete i->second;
	}
	TTF_CloseFont(font);
	TTF_Quit();
	// Delete singleton game
	delete GameObjectFactory::Instance();
	delete textureManager::Instance();
	delete Collision::Instance();
	delete instance;
	SDL_Quit();
}

void Game::update(){
	for(std::vector<SDLGameObject*>::iterator i = floors[currentFloor]->enemies.begin(); i != floors[currentFloor]->enemies.end(); ++i) {
		if((*i) != nullptr) {
		  (*i)->update();
		}
	}
}

void Game::handleEvents(){
	SDL_Event Event;
	if(SDL_PollEvent(&Event)){
		if(Event.type == SDL_QUIT) {
			Running = false;
		}
		else if(Event.type == SDL_KEYDOWN) {
			int position;
			char stairType;
			switch(Event.key.keysym.sym) {
			case SDLK_UP :
				player->setRow(3);
				player->setFrame(0);
				if(Collision::Instance()->detectKey(&(floors[currentFloor]->keys),player,'N',32,position) == false) {
				   if(Collision::Instance()->detectJewel(&(floors[currentFloor]->jewels),player,'N',32,position) == false) {
					   if(Collision::Instance()->detectMedicine(&(floors[currentFloor]->medicines),player,'N',32,position) == false) {
						   if(Collision::Instance()->detectDoorExist(&(floors[currentFloor]->doors),player,'N',32,position) == false) {
							   if(Collision::Instance()->detectEnemyExist(&(floors[currentFloor]->enemies),player,'N',32,position) == false) {
								  if(Collision::Instance()->detectWall(&(floors[currentFloor]->map),player,'N',32) == false) {
									  if(Collision::Instance()->detectStair(&(floors[currentFloor]->stairs), player, 'N',32,stairType) == false) {
									    if(player->getY() >= 64) {
                                            player->decreaseY();
									    }
									  }
									  else {
										  if(stairType == 'U'){
										     ++currentFloor;
										     // Set Player coordinate
										     for(std::vector<SDLGameObject*>::iterator i = floors[currentFloor]->stairs.begin(); i != floors[currentFloor]->stairs.end(); i++) {
											     if(dynamic_cast<Stair*>(*i)->type == 'D') {
												     dynamic_cast<Player*>(player)->setX((*i)->getX());
												     dynamic_cast<Player*>(player)->setY((*i)->getY());
											     }
										     }
											 textureManager::Instance()->changeFloor(renderer,font,currentFloor);
										  }
										  else {
											--currentFloor;
											for(std::vector<SDLGameObject*>::iterator i = floors[currentFloor]->stairs.begin(); i != floors[currentFloor]->stairs.end(); i++) {
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
							   else {
								   if(Collision::Instance()->detectCanFightWithEnemy(&(floors[currentFloor]->enemies),player,'N',32,position) == false) {
								     }
								   else {
									   int PlayerHP = dynamic_cast<Player*>(player)->getHP();
	                                   int EnemyHP = dynamic_cast<Enemy*>((floors[currentFloor]->enemies)[position])->getHP();
		                               int P_E_damage = (100.0 / (100 + dynamic_cast<Enemy*>((floors[currentFloor]->enemies)[position])->getDefence())) * dynamic_cast<Player*>(player)->getAttack();
		                               int E_P_damage = (100.0 / (100 + dynamic_cast<Player*>(player)->getDefence())) * dynamic_cast<Enemy*>((floors[currentFloor]->enemies)[position])->getAttack();
									   unsigned int lastTime = SDL_GetTicks();
									   while(true) {
										   if(Collision::Instance()->fight(&(floors[currentFloor]->enemies),player,'N',32,position,renderer,font,PlayerHP,EnemyHP,P_E_damage,E_P_damage,lastTime) == true) {
											   // Print the winning message
											   textureManager::Instance()->drawMessage("win",position,&(floors[currentFloor]->enemies),renderer,&background,floors[currentFloor],player,font);
											   // Reset Player HP 
											   dynamic_cast<Player*>(player)->setHP(PlayerHP - dynamic_cast<Player*>(player)->getHP());
											   dynamic_cast<Player*>(player)->setGold(dynamic_cast<Enemy*>(floors[currentFloor]->enemies[position])->getGold());
											   dynamic_cast<Player*>(player)->setExperience(dynamic_cast<Enemy*>(floors[currentFloor]->enemies[position])->getExperience());
											   delete (floors[currentFloor]->enemies)[position];
											   (floors[currentFloor]->enemies)[position] = nullptr;
											   break;
										   }
										   else {
											   // Print the fighting message
                                               textureManager::Instance()->drawMessage("fight",position,&(floors[currentFloor]->enemies),renderer,&background,floors[currentFloor],player,font,PlayerHP,EnemyHP);
										   }
									   }
								   }
							   }
						   }
						   else {
							   while(!Collision::Instance()->detectDoor(&(floors[currentFloor]->doors),player,'N',32,position)) {
								   render();
							   }
							   render();
						   }
					   }
					   else {
						   textureManager::Instance()->drawMessage("medicine",position,&(floors[currentFloor]->medicines),renderer,&background,floors[currentFloor],player,font);
						   // Print Medicine message here
					   }
				   }
				   else {
					   textureManager::Instance()->drawMessage("jewel",position,&(floors[currentFloor]->jewels),renderer,&background,floors[currentFloor],player,font);
					   // Print Jewel message here
				   }
				}
				else {
					textureManager::Instance()->drawMessage("key",position,&(floors[currentFloor]->keys),renderer,&background,floors[currentFloor],player,font);
					// Print Key message here
				}
				break;
			case SDLK_DOWN:
				player->setRow(0);
				player->setFrame(0);
				if(Collision::Instance()->detectKey(&(floors[currentFloor]->keys), player,'S',32,position) == false) {
				   if(Collision::Instance()->detectJewel(&(floors[currentFloor]->jewels),player,'S',32,position) == false) {
					   if(Collision::Instance()->detectMedicine(&(floors[currentFloor]->medicines),player,'S',32,position) == false) {
						   if(Collision::Instance()->detectDoorExist(&(floors[currentFloor]->doors),player,'S',32,position) == false) {
							   if(Collision::Instance()->detectEnemyExist(&(floors[currentFloor]->enemies),player,'S',32,position) == false) {
								   if(Collision::Instance()->detectWall(&(floors[currentFloor]->map),player,'S',32) == false) {
									   if(Collision::Instance()->detectStair(&(floors[currentFloor]->stairs), player, 'S',32,stairType) == false) {
									     if(player->getY() <= 320) {
				                            player->increaseY();
									     }
									   }
									   else {
										   if(stairType == 'U'){
										     ++currentFloor;
										     // Set Player coordinate
										     for(std::vector<SDLGameObject*>::iterator i = floors[currentFloor]->stairs.begin(); i != floors[currentFloor]->stairs.end(); i++) {
											     if(dynamic_cast<Stair*>(*i)->type == 'D') {
												     dynamic_cast<Player*>(player)->setX((*i)->getX());
												     dynamic_cast<Player*>(player)->setY((*i)->getY());
											     }
										     }
											 textureManager::Instance()->changeFloor(renderer,font,currentFloor);
										  }
										  else {
											--currentFloor;
											for(std::vector<SDLGameObject*>::iterator i = floors[currentFloor]->stairs.begin(); i != floors[currentFloor]->stairs.end(); i++) {
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
							   else {
								   if(Collision::Instance()->detectCanFightWithEnemy(&(floors[currentFloor]->enemies),player,'S',32,position) == false) {
								    }
								   else {
									   int PlayerHP = dynamic_cast<Player*>(player)->getHP();
	                                   int EnemyHP = dynamic_cast<Enemy*>((floors[currentFloor]->enemies)[position])->getHP();
		                               int P_E_damage = (100.0 / (100 + dynamic_cast<Enemy*>((floors[currentFloor]->enemies)[position])->getDefence())) * dynamic_cast<Player*>(player)->getAttack();
		                               int E_P_damage = (100.0 / (100 + dynamic_cast<Player*>(player)->getDefence())) * dynamic_cast<Enemy*>((floors[currentFloor]->enemies)[position])->getAttack();
									   unsigned int lastTime = SDL_GetTicks();
									   while(true) {
										   if(Collision::Instance()->fight(&(floors[currentFloor]->enemies),player,'S',32,position,renderer,font,PlayerHP,EnemyHP,P_E_damage,E_P_damage,lastTime) == true) {
											   // Print the winning message
                                               textureManager::Instance()->drawMessage("win",position,&(floors[currentFloor]->enemies),renderer,&background,floors[currentFloor],player,font);
											   dynamic_cast<Player*>(player)->setHP(PlayerHP - dynamic_cast<Player*>(player)->getHP());
											   dynamic_cast<Player*>(player)->setGold(dynamic_cast<Enemy*>(floors[currentFloor]->enemies[position])->getGold());
											   dynamic_cast<Player*>(player)->setExperience(dynamic_cast<Enemy*>(floors[currentFloor]->enemies[position])->getExperience());
											   delete (floors[currentFloor]->enemies[position]);
											   floors[currentFloor]->enemies[position] = nullptr;
											   break;
										   }
										   else {
											   // Print the fighting message
                                               textureManager::Instance()->drawMessage("fight",position,&(floors[currentFloor]->enemies),renderer,&background,floors[currentFloor],player,font,PlayerHP,EnemyHP);
										   }
									   }
								   }
							   }
						   }
						   else {
							   while(!Collision::Instance()->detectDoor(&(floors[currentFloor]->doors),player,'S',32,position)) {
								   render();
							   }
							   render();
						   }
					   }
					   else {
						   // Print Medicine message here
						   textureManager::Instance()->drawMessage("medicine",position,&(floors[currentFloor]->medicines),renderer,&background,floors[currentFloor],player,font);
					   }
				   }
				   else {
					   // Print Jewel message here
					   textureManager::Instance()->drawMessage("jewel",position,&(floors[currentFloor]->jewels),renderer,&background,floors[currentFloor],player,font);
				   }
				}
				else {
					// Print Key message here
					textureManager::Instance()->drawMessage("key",position,&(floors[currentFloor]->keys),renderer,&background,floors[currentFloor],player,font);
				}
				break;
			case SDLK_LEFT:
				player->setRow(1);
				player->setFrame(0);
				if(Collision::Instance()->detectKey(&(floors[currentFloor]->keys), player,'W',32,position) == false) {
				   if(Collision::Instance()->detectJewel(&(floors[currentFloor]->jewels),player,'W',32,position) == false) {
					   if(Collision::Instance()->detectMedicine(&(floors[currentFloor]->medicines),player,'W',32,position) == false) {
						   if(Collision::Instance()->detectDoorExist(&(floors[currentFloor]->doors),player,'W',32,position) == false) {
							   if(Collision::Instance()->detectEnemyExist(&(floors[currentFloor]->enemies),player,'W',32,position) == false) {
								   if(Collision::Instance()->detectWall(&(floors[currentFloor]->map),player,'W',32) == false) {
									   if(Collision::Instance()->detectStair(&(floors[currentFloor]->stairs), player, 'W',32,stairType) == false) {
									     if(player->getX() >= 224) {
				                            player->decreaseX();
									     }
									   }
									   else {
										  if(stairType == 'U'){
										     ++currentFloor;
										     // Set Player coordinate
										     for(std::vector<SDLGameObject*>::iterator i = floors[currentFloor]->stairs.begin(); i != floors[currentFloor]->stairs.end(); i++) {
											     if(dynamic_cast<Stair*>(*i)->type == 'D') {
												     dynamic_cast<Player*>(player)->setX((*i)->getX());
												     dynamic_cast<Player*>(player)->setY((*i)->getY());
											     }
										     }
											 textureManager::Instance()->changeFloor(renderer,font,currentFloor);
										  }
										  else {
											--currentFloor;
											for(std::vector<SDLGameObject*>::iterator i = floors[currentFloor]->stairs.begin(); i != floors[currentFloor]->stairs.end(); i++) {
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
							   else {
								   if(Collision::Instance()->detectCanFightWithEnemy(&(floors[currentFloor]->enemies),player,'W',32,position) == false) {
								   }
								   else {
									   int PlayerHP = dynamic_cast<Player*>(player)->getHP();
	                                   int EnemyHP = dynamic_cast<Enemy*>((floors[currentFloor]->enemies)[position])->getHP();
		                               int P_E_damage = (100.0 / (100 + dynamic_cast<Enemy*>((floors[currentFloor]->enemies)[position])->getDefence())) * dynamic_cast<Player*>(player)->getAttack();
		                               int E_P_damage = (100.0 / (100 + dynamic_cast<Player*>(player)->getDefence())) * dynamic_cast<Enemy*>((floors[currentFloor]->enemies)[position])->getAttack();
									   unsigned int lastTime = SDL_GetTicks();
									   while(true) {
										   if(Collision::Instance()->fight(&(floors[currentFloor]->enemies),player,'W',32,position,renderer,font,PlayerHP,EnemyHP,P_E_damage,E_P_damage,lastTime) == true) {
											   // Print the winning message
                                               textureManager::Instance()->drawMessage("win",position,&(floors[currentFloor]->enemies),renderer,&background,floors[currentFloor],player,font);
											   dynamic_cast<Player*>(player)->setHP(PlayerHP - dynamic_cast<Player*>(player)->getHP());
											   dynamic_cast<Player*>(player)->setGold(dynamic_cast<Enemy*>(floors[currentFloor]->enemies[position])->getGold());
											   dynamic_cast<Player*>(player)->setExperience(dynamic_cast<Enemy*>(floors[currentFloor]->enemies[position])->getExperience());
											   delete (floors[currentFloor]->enemies[position]);
											   floors[currentFloor]->enemies[position] = nullptr;
											   break;
										   }
										   else {
											   // Print the fighting message
                                               textureManager::Instance()->drawMessage("fight",position,&(floors[currentFloor]->enemies),renderer,&background,floors[currentFloor],player,font,PlayerHP,EnemyHP);
										   }
									   }
								   }
							   }
						   }
						   else {
							   while(!Collision::Instance()->detectDoor(&(floors[currentFloor]->doors),player,'W',32,position)) {
								   render();
							   }
							   render();
						   }
					   }
					   else {
						   // Print Medicine Message here
						   textureManager::Instance()->drawMessage("medicine",position,&(floors[currentFloor]->medicines),renderer,&background,floors[currentFloor],player,font);
					   }
				   }
				   else {
					   // Print Jewel Message here
					   textureManager::Instance()->drawMessage("jewel",position,&(floors[currentFloor]->jewels),renderer,&background,floors[currentFloor],player,font);
				   }
				}
				else {
					// Print Key Message here
					textureManager::Instance()->drawMessage("key",position,&(floors[currentFloor]->keys),renderer,&background,floors[currentFloor],player,font);
				}
				break;
			case SDLK_RIGHT:
				player->setRow(2);
				player->setFrame(0);
				if(Collision::Instance()->detectKey(&(floors[currentFloor]->keys), player,'E',32,position) == false) {
				   if(Collision::Instance()->detectJewel(&(floors[currentFloor]->jewels),player,'E',32,position) == false) {
					   if(Collision::Instance()->detectMedicine(&(floors[currentFloor]->medicines),player,'E',32,position) == false) {
						   if(Collision::Instance()->detectDoorExist(&(floors[currentFloor]->doors),player,'E',32,position) == false) {
							   if(Collision::Instance()->detectEnemyExist(&(floors[currentFloor]->enemies),player,'E',32,position) == false) {
								   if(Collision::Instance()->detectWall(&(floors[currentFloor]->map),player,'E',32) == false) {
									   if(Collision::Instance()->detectStair(&(floors[currentFloor]->stairs), player, 'E',32,stairType) == false) {
									     if(player->getX() <= 480) {
				                            player->increaseX();
									     }
									   }
									   else {
										  if(stairType == 'U'){
										     ++currentFloor;
										     // Set Player coordinate
										     for(std::vector<SDLGameObject*>::iterator i = floors[currentFloor]->stairs.begin(); i != floors[currentFloor]->stairs.end(); i++) {
											     if(dynamic_cast<Stair*>(*i)->type == 'D') {
												     dynamic_cast<Player*>(player)->setX((*i)->getX());
												     dynamic_cast<Player*>(player)->setY((*i)->getY());
											     }
										     }
											 textureManager::Instance()->changeFloor(renderer,font,currentFloor);
										  }
										  else {
											--currentFloor;
											for(std::vector<SDLGameObject*>::iterator i = floors[currentFloor]->stairs.begin(); i != floors[currentFloor]->stairs.end(); i++) {
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
							   else {
								   if(Collision::Instance()->detectCanFightWithEnemy(&(floors[currentFloor]->enemies),player,'E',32,position) == false) {
								   }
								   else {
									   int PlayerHP = dynamic_cast<Player*>(player)->getHP();
	                                   int EnemyHP = dynamic_cast<Enemy*>((floors[currentFloor]->enemies)[position])->getHP();
		                               int P_E_damage = (100.0 / (100 + dynamic_cast<Enemy*>((floors[currentFloor]->enemies)[position])->getDefence())) * dynamic_cast<Player*>(player)->getAttack();
		                               int E_P_damage = (100.0 / (100 + dynamic_cast<Player*>(player)->getDefence())) * dynamic_cast<Enemy*>((floors[currentFloor]->enemies)[position])->getAttack();
									   unsigned int lastTime = SDL_GetTicks();
									   while(true) {
										   if(Collision::Instance()->fight(&(floors[currentFloor]->enemies),player,'E',32,position,renderer,font,PlayerHP,EnemyHP,P_E_damage,E_P_damage,lastTime) == true) {
											   // Print the winning message
                                               textureManager::Instance()->drawMessage("win",position,&(floors[currentFloor]->enemies),renderer,&background,floors[currentFloor],player,font);
											   dynamic_cast<Player*>(player)->setHP(PlayerHP - dynamic_cast<Player*>(player)->getHP());
											   dynamic_cast<Player*>(player)->setGold(dynamic_cast<Enemy*>(floors[currentFloor]->enemies[position])->getGold());
											   dynamic_cast<Player*>(player)->setExperience(dynamic_cast<Enemy*>(floors[currentFloor]->enemies[position])->getExperience());
											   delete (floors[currentFloor]->enemies[position]);
											   floors[currentFloor]->enemies[position] = nullptr;
											   break;
										   }
										   else {
											   // Print the fighting message
                                               textureManager::Instance()->drawMessage("fight",position,&(floors[currentFloor]->enemies),renderer,&background,floors[currentFloor],player,font,PlayerHP,EnemyHP);
										   }
									   }
								   }
							   }
						   }
						   else {
							   while(!Collision::Instance()->detectDoor(&(floors[currentFloor]->doors),player,'E',32,position)) {
								   render();
							   }
							   render();
						   }
					   }
					   else {
						   // Print Medicine message here
						   textureManager::Instance()->drawMessage("medicine",position,&(floors[currentFloor]->medicines),renderer,&background,floors[currentFloor],player,font);
					   }
				   }
				   else {
					   // Print Jewel message here
					   textureManager::Instance()->drawMessage("jewel",position,&(floors[currentFloor]->jewels),renderer,&background,floors[currentFloor],player,font);
				   }
				}
				else {
					// Print Key message here
					textureManager::Instance()->drawMessage("key",position,&(floors[currentFloor]->keys),renderer,&background,floors[currentFloor],player,font);
				}
				break;
			}
		}
		else if(Event.type == SDL_KEYUP) {
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

bool Game::running() { return Running;}

void Game::gameover() { Running = false;}

SDL_Renderer* Game::getRenderer() const{
	return renderer;
}