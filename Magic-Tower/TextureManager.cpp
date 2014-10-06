/* Copyright (C) 2014   Susu Dong
   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely.
*/

#include <iostream>
#include <sstream>
#include "TextureManager.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Player.h"
#include "Enemy.h"
#include "Floor.h"
using namespace std;

// Store the SDL_color. Needs to be pre-declared like this
// Trying to figure out why....
static const SDL_Color DARKYELLOW = {255,156,0};
static const SDL_Color YELLOW     = {255,255,0};
static const SDL_Color RED        = {255,0,60};
static const SDL_Color GREEN      = {0,255,0};
static const SDL_Color BLUE      =  {0,131,255};

textureManager* textureManager::instan = nullptr;

textureManager::textureManager(){}

textureManager::~textureManager(){}

// Singleton textureManager !
textureManager* textureManager::Instance() {
	if(instan == nullptr) {
		instan = new textureManager();
	}
	return instan;
}

// Load the sprite sheet
bool textureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer) {
	SDL_Surface* temp;
	// Loading the file using IMG_Load() function from SDL_image library
	if((temp = IMG_Load(fileName.c_str())) == nullptr) {
		cerr << IMG_GetError() << endl;
		return false;
	}
	// Transform SDL_Surface* to SDL_Texture* using SDL_CreateTextureFromSurface
	SDL_Texture* texture = SDL_CreateTextureFromSurface(pRenderer,temp);

	// Free useless temp(SDL_Surface*), we are now using SDL_Texture*
	SDL_FreeSurface(temp);
	if(texture != nullptr) {
		textureMap[id] = texture;
		return true;
	}
	return false;
}

// Render static pictures
void textureManager::draw(std::string id, 
	                      int x, 
						  int y, 
						  int width,
						  int height, 
	                      SDL_Renderer* pRenderer, 
						  SDL_RendererFlip flip) {
    // Define two SDL_Rect struct
	SDL_Rect srcRect;
	SDL_Rect destRect;

	// Set the start point of the image we are using to (0,0)
	srcRect.x = srcRect.y = 0;
	destRect.x = x;
	destRect.y = y;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;

	// Leave angle and center to be 0 
	SDL_RenderCopyEx(pRenderer,textureMap[id],&srcRect,&destRect,0,0,flip);
}

// Difference to draw() function defined above is here
// we are using currentFrame and currentRow to determine which
// part of the sprite sheet we are using in a serial of pictures to simulate animation
void textureManager::drawFrame(std::string id, 
	                           int x, 
							   int y, 
							   int width, 
							   int height,  
							   int currentRow, 
							   int currentFrame,
	                           SDL_Renderer* pRenderer, 
							   SDL_RendererFlip flip) {
	// Defining two SDL_Rect struct
	SDL_Rect srcRect;
	SDL_Rect destRect;
	
	// Get the exact position of the sprite sheet
	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;

	destRect.x = x;
	destRect.y = y;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	SDL_RenderCopyEx(pRenderer,textureMap[id],&srcRect,&destRect,0,0,flip);
}

// Draw the status of the player on the top left of the game screen
void textureManager::drawStatus(std::string heroID, 
	                            std::string itemID, 
								SDLGameObject* player, 
								SDL_Renderer* pRenderer, 
								TTF_Font* font, 
								SDL_RendererFlip flip) {
	// Variables to be used through out the rendering part
	SDL_Color white = { 255, 255, 255 }; 
	SDL_Rect destRect;
	SDL_Surface* level;
	SDL_Texture* texture_Level;

	// Go!
	draw(heroID,32,27,32,32,pRenderer);

	// Render Level
	stringstream ss1;
	ss1 << dynamic_cast<Player*>(player)->getLevel();
	string Level = "Level " + ss1.str();
	level = TTF_RenderText_Solid(font,Level.c_str(),white); // TTF_RenderText only accept C style string
	texture_Level = SDL_CreateTextureFromSurface(pRenderer,level);
	// Specify destination to be rendered
	destRect.x = 112;
	destRect.y = 35;
	destRect.h = level->h;
	destRect.w = level->w;
	// Now render level info!
	SDL_RenderCopyEx(pRenderer,texture_Level,NULL,&destRect,0,0,SDL_FLIP_NONE);
	// IMPORTANT !! Need to be freed before being used again
    SDL_FreeSurface(level);
	SDL_DestroyTexture(texture_Level);


	// Render HP
	stringstream ss2;
	ss2 << dynamic_cast<Player*>(player)->getHP();
	string Hp = "HP      " + ss2.str();
	level = TTF_RenderText_Solid(font,Hp.c_str(),white);
	texture_Level = SDL_CreateTextureFromSurface(pRenderer,level);
	// Specify destination to be rendered
	destRect.x = 33;
	destRect.y = 65;
	destRect.h = level->h;
	destRect.w = level->w;
	// Now render HP info!
	SDL_RenderCopyEx(pRenderer,texture_Level,NULL,&destRect,0,0,SDL_FLIP_NONE);
	// IMPORTANT !! Need to be freed before being used again
    SDL_FreeSurface(level);
	SDL_DestroyTexture(texture_Level);


	// Render Attack
	stringstream ss3;
	ss3 << dynamic_cast<Player*>(player)->getAttack();
	string Attack = "Attack   " + ss3.str();
	level = TTF_RenderText_Solid(font,Attack.c_str(),white);
	texture_Level = SDL_CreateTextureFromSurface(pRenderer,level);
	// Specify destination to be rendered
	destRect.x = 33;
	destRect.y = 95;
	destRect.h = level->h;
	destRect.w = level->w;
	// Now render attack info!
	SDL_RenderCopyEx(pRenderer,texture_Level,NULL,&destRect,0,0,SDL_FLIP_NONE);
	// IMPORTANT !! Need to be freed before being used again
    SDL_FreeSurface(level);
	SDL_DestroyTexture(texture_Level);

	
	// Render Defence
	stringstream ss4;
	ss4 << dynamic_cast<Player*>(player)->getDefence();
	string Defence = "Defence  " + ss4.str();
	level = TTF_RenderText_Solid(font,Defence.c_str(),white);
	texture_Level = SDL_CreateTextureFromSurface(pRenderer,level);
	// Specify destination to be rendered
	destRect.x = 33;
	destRect.y = 125;
	destRect.h = level->h;
	destRect.w = level->w;
	// Now render defence info!
	SDL_RenderCopyEx(pRenderer,texture_Level,NULL,&destRect,0,0,SDL_FLIP_NONE);
	// IMPORTANT !! Need to be freed before being used again
    SDL_FreeSurface(level);
	SDL_DestroyTexture(texture_Level);


	// Render Gold
	stringstream ss5;
	ss5 << dynamic_cast<Player*>(player)->getGold();
	string Gold = "gold     " + ss5.str();
	level = TTF_RenderText_Solid(font,Gold.c_str(),white);
	texture_Level = SDL_CreateTextureFromSurface(pRenderer,level);
	// Specify destination to be rendered
	destRect.x = 33;
	destRect.y = 155;
	destRect.h = level->h;
	destRect.w = level->w;
	// Now render gold info!
	SDL_RenderCopyEx(pRenderer,texture_Level,NULL,&destRect,0,0,SDL_FLIP_NONE);
	// IMPORTANT !! Need to be freed before being used again
    SDL_FreeSurface(level);
	SDL_DestroyTexture(texture_Level);


	// Render Experience
	stringstream ss6;
	ss6 << dynamic_cast<Player*>(player)->getExperience();
	string Exp = "Exp      " + ss6.str();
	level = TTF_RenderText_Solid(font,Exp.c_str(),white);
	texture_Level = SDL_CreateTextureFromSurface(pRenderer,level);
	// Specify destination to be rendered
	destRect.x = 33;
	destRect.y = 185;
	destRect.h = level->h;
	destRect.w = level->w;
	// Now render experience info!
	SDL_RenderCopyEx(pRenderer,texture_Level,NULL,&destRect,0,0,SDL_FLIP_NONE);
	// IMPORTANT !! Need to be freed before being used again
    SDL_FreeSurface(level);
	SDL_DestroyTexture(texture_Level);


    // Render Yellow Keys
	drawFrame(itemID,33,215,32,32,4,0,pRenderer);
	stringstream ss7;
	ss7 << dynamic_cast<Player*>(player)->getYellowKey();
	string Yellow = ss7.str();
	level = TTF_RenderText_Solid(font,Yellow.c_str(),white);
	texture_Level = SDL_CreateTextureFromSurface(pRenderer,level);
	// Specify destination to be rendered
	destRect.x = 138;
	destRect.y = 215;
	destRect.h = level->h;
	destRect.w = level->w;
	// Now render yellow key info!
	SDL_RenderCopyEx(pRenderer,texture_Level,NULL,&destRect,0,0,SDL_FLIP_NONE);
	// IMPORTANT !! Need to be freed before being used again
    SDL_FreeSurface(level);
	SDL_DestroyTexture(texture_Level);


	// Render Red Key
	drawFrame(itemID,33,245,32,32,4,2,pRenderer);
	stringstream ss8;
	ss8 << dynamic_cast<Player*>(player)->getRedKey();
	string Red = ss8.str();
	level = TTF_RenderText_Solid(font,Red.c_str(),white);
	texture_Level = SDL_CreateTextureFromSurface(pRenderer,level);
	// Specify destination to be rendered
	destRect.x = 138;
	destRect.y = 245;
	destRect.h = level->h;
	destRect.w = level->w;
	// Now render red key info!
	SDL_RenderCopyEx(pRenderer,texture_Level,NULL,&destRect,0,0,SDL_FLIP_NONE);
	// IMPORTANT !! Need to be freed before being used again
    SDL_FreeSurface(level);
	SDL_DestroyTexture(texture_Level);

	// Render Blue Key
	drawFrame(itemID,33,275,32,32,4,1,pRenderer);
	stringstream ss9;
	ss9 << dynamic_cast<Player*>(player)->getBlueKey();
	string Blue = ss9.str();
	level = TTF_RenderText_Solid(font,Blue.c_str(),white);
	texture_Level = SDL_CreateTextureFromSurface(pRenderer,level);
	// Specify destination to be rendered
	destRect.x = 138;
	destRect.y = 275;
	destRect.h = level->h;
	destRect.w = level->w;
	// Now render blue key info!
	SDL_RenderCopyEx(pRenderer,texture_Level,NULL,&destRect,0,0,SDL_FLIP_NONE);
	// IMPORTANT !! Need to be freed before being used again
    SDL_FreeSurface(level);
	SDL_DestroyTexture(texture_Level);
}


// Draw the animation of fight with messages printed out powered by an outside while loop in Game.cpp
void textureManager::drawFight(std::string heroID, 
	                           std::string enemyID, 
							   SDLGameObject* player, 
							   SDLGameObject* enemy, 
							   SDL_Renderer* pRenderer, 
							   TTF_Font* font, 
							   bool win, 
	                           int playerHP, 
							   int enemyHP, 
							   SDL_RendererFlip flip) {
	SDL_Color white = { 255, 255, 255 };
	SDL_Surface* level;
	SDL_Texture* texture_Level;
	SDL_Rect destRect;
	stringstream ss1; 
	stringstream ss2;
	if(win) {
		ss1 << dynamic_cast<Enemy*>(enemy)->getGold();
		ss2 << dynamic_cast<Enemy*>(enemy)->getExperience();
		string gold = ss1.str();
		string experience = ss2.str();
		string total = "You win. " + gold + " golds and " + experience + " exp points gained.";
		level = TTF_RenderText_Solid(font,total.c_str(),white); 
		texture_Level = SDL_CreateTextureFromSurface(pRenderer,level);
		destRect.x = 100;
	    destRect.y = 420;
	    destRect.h = level->h;
	    destRect.w = level->w;
	}
	else {
		// If still in fight, continue drawing the player and the enemy
		draw(heroID,198,420,32,32,pRenderer);
		drawFrame(enemyID,294,420,32,32,enemy->getRow(),0,pRenderer);
		ss1 << playerHP;
		ss2 << enemyHP;
		string p = ss1.str();
		string e = ss2.str();
		string total = "HP    " + p + "      " + e;
		level = TTF_RenderText_Solid(font,total.c_str(),white); 
		texture_Level = SDL_CreateTextureFromSurface(pRenderer,level);
		destRect.x = 128;
	    destRect.y = 480;
	    destRect.h = level->h;
	    destRect.w = level->w;
	}
	SDL_RenderCopyEx(pRenderer,texture_Level,NULL,&destRect,0,0,SDL_FLIP_NONE);
	// IMPORTANT! Need to be freed!
    SDL_FreeSurface(level);
	SDL_DestroyTexture(texture_Level);
}

// Draw different messages due to different events fired
void textureManager::drawMessage(std::string messageType, 
	                             int position, 
								 std::vector<SDLGameObject*> *things, 
								 SDL_Renderer* renderer, 
		                         std::vector<std::vector<SDLGameObject*> >* background, 
								 Floor* floor, 
								 SDLGameObject* player, 
								 TTF_Font* font, 
								 int playerHP, 
								 int enemyHP) {
						 // Get current time in order to achieve a 0.5 s stay of message on the screen
						 unsigned int lastTime = SDL_GetTicks();
						 SDL_Color color;
	                     SDL_Surface* level;
	                     SDL_Texture* texture_Level;
	                     SDL_Rect destRect;
						 if(messageType == "key" || messageType == "medicine" || messageType == "jewel") {
							 while(true) {
								// Get current time to make the message stay on the screen for 0.5 s
								unsigned int currentTime = SDL_GetTicks();
						  	    if(currentTime > lastTime + 500) {
									   break;
							    }
							    else {
								       SDL_RenderClear(renderer); // Need to clear first, otherwise images will overlap on the screen
	                                   for(std::vector<std::vector<SDLGameObject*> >::iterator i = background->begin(); i != background->end(); ++i) {
		                                     for(std::vector<SDLGameObject*>::iterator j = (*i).begin(); j != (*i).end(); ++j) {
			                                         (*j)->draw();
		                                     }
	                                   }
	                                   floor->render();
	                                   player->draw();
									   drawStatus("hero","item",player,renderer,font);
									   string total;
									   if(messageType == "key"){
									       if((*things)[position]->getColor() == "yellow") { // The position is location of item in the vector where the player had collision with
											       color = DARKYELLOW ;
		                                           total = "A yellow key gained.";
									       }
									       else if((*things)[position]->getColor() == "red") {
											       color = RED;
										           total = "A red key gained.";
									       } 
									       else {
											       color = BLUE;
										           total = "A blue key gained.";
									       }
									   }
									   else if(messageType == "medicine") {
										   if((*things)[position]->getColor() == "red") {
											       color = RED;
										           total = "50 HP recover.";
									       } 
										   else if((*things)[position]->getColor() == "blue") {
											       color = BLUE;
										           total = "100 HP recover.";
									       } 
										   else if((*things)[position]->getColor() == "green") {
											       color = GREEN;
										           total = "150 HP recover.";
									       } 
										   else if((*things)[position]->getColor() == "yellow") {
											       color = YELLOW;
										           total = "200 HP recover.";
									       }
										   else {
											       
										   }
									   }
									   else {
										   if((*things)[position]->getColor() == "red") {
											       color = RED;
										           total = "3 points of attack increased.";
									       } 
										   else if((*things)[position]->getColor() == "blue") {
											       color = BLUE;
										           total = "2 points of defence increased.";
									       } 
										   else if((*things)[position]->getColor() == "green") {
                                                   color = GREEN;
										           total = "7 points of attack increased.";
									       } 
										   else if((*things)[position]->getColor() == "yellow") {
											       color = YELLOW;
										           total = "5 points of defence increased.";
									       } 
										   else {
										   }
									   }
									   level = TTF_RenderText_Solid(font,total.c_str(),color); 
		                               texture_Level = SDL_CreateTextureFromSurface(renderer,level);
		                               destRect.x = 150;
	                                   destRect.y = 450;
	                                   destRect.h = level->h;
	                                   destRect.w = level->w;
									   SDL_RenderCopyEx(renderer,texture_Level,NULL,&destRect,0,0,SDL_FLIP_NONE);
	                                   SDL_RenderPresent(renderer);
									   // IMPORTANT! Free!
									   SDL_FreeSurface(level);
	                                   SDL_DestroyTexture(texture_Level);
									   SDL_Event Event;
									   // Make sure user inputs get consumed at this stage to prevent them got caught in Game.cpp
									   while(SDL_PollEvent(&Event)){ }
									   }
							  }
							 // Clean up
							 delete (*things)[position];
							 (*things)[position] = nullptr;
						 }
						 else if(messageType == "win") {
							 	 while(true) {
										unsigned int currentTime = SDL_GetTicks();
										if(currentTime > lastTime + 1000) {
												break;
										}
										else {
											SDL_RenderClear(renderer);
	                                        for(std::vector<std::vector<SDLGameObject*> >::iterator i = background->begin(); i != background->end(); ++i) {
		                                         for(std::vector<SDLGameObject*>::iterator j = (*i).begin(); j != (*i).end(); ++j) {
			                                             (*j)->draw();
		                                         }
	                                        }
	                                        floor->render();
	                                        player->draw();
			                                drawStatus("hero","item",player,renderer,font);
											drawFight("hero","enemy",player,(floor->enemies)[position],renderer,font,true,0,0);
	                                        SDL_RenderPresent(renderer);
										    SDL_Event Event;
										    while(SDL_PollEvent(&Event)){ }
										}
									}
						 }
						 else if(messageType == "fight") {
							       SDL_RenderClear(renderer);
	                               for(std::vector<std::vector<SDLGameObject*> >::iterator i = background->begin(); i != background->end(); ++i) {
		                                 for(std::vector<SDLGameObject*>::iterator j = (*i).begin(); j != (*i).end(); ++j) {
			                                     (*j)->draw();
		                                 }
	                               }
	                               floor->render();
	                               player->draw();
                                   drawStatus("hero","item",player,renderer,font);
						           drawFight("hero","enemy",player,(floor->enemies)[position],renderer,font,false,playerHP,enemyHP);
	                               SDL_RenderPresent(renderer);
							       SDL_Event Event;
							       while(SDL_PollEvent(&Event)){ }
						 }
						 else if(messageType == "weapon") {
							 // TODO;
						 }
						 else {
							 // TODO; add more items
						 }
}

// Make a black screen!
void textureManager::changeFloor(SDL_Renderer* pRenderer, 
	                             TTF_Font* font, 
								 int floor) {
	unsigned int lastTime = SDL_GetTicks();
	SDL_Color white = { 255, 255, 255 };
	SDL_Surface* level;
	SDL_Texture* texture_Level;
	SDL_Rect destRect;
	while(true) {
		unsigned int currentTime = SDL_GetTicks();
		// Make the screen black for 1 s with white message gets printed out
		if(currentTime > lastTime + 1000) {
				break;
		}
		else {
			SDL_RenderClear(pRenderer);
			stringstream ss;
	        ss << floor;
	        string total = "Floor " + ss.str();
			level = TTF_RenderText_Solid(font,total.c_str(),white); 
		    texture_Level = SDL_CreateTextureFromSurface(pRenderer,level);
		    destRect.x = 260;
	        destRect.y = 288;
	        destRect.h = level->h;
	        destRect.w = level->w;
			// Now render floor info at the center of the screen
		    SDL_RenderCopyEx(pRenderer,texture_Level,NULL,&destRect,0,0,SDL_FLIP_NONE);
	        SDL_RenderPresent(pRenderer);
			// IMPORTANT! Free!
			SDL_FreeSurface(level);
	        SDL_DestroyTexture(texture_Level);
			SDL_Event Event;
		    // Make sure user inputs get consumed at this stage to prevent them got caught in Game.cpp
		    while(SDL_PollEvent(&Event)){ }
		    }
	}
}