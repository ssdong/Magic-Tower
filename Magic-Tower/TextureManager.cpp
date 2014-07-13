/* 
   TextureManager.cpp and TextureManager.h

   Notice, draw and drawFrame codes are from "SDL Game Development"

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
#include <sstream>
#include "TextureManager.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Player.h"
#include "Enemy.h"
#include "Floor.h"
using namespace std;

textureManager* textureManager::instan = nullptr;

textureManager::textureManager(){}

textureManager::~textureManager(){}

textureManager* textureManager::Instance() {
	if(instan == nullptr) {
		instan = new textureManager();
	}
	return instan;
}
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

void textureManager::draw(std::string id, int x, int y, int width, int height, 
	                      SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
    // Defining two SDL_Rect struct
	SDL_Rect srcRect;
	SDL_Rect destRect;

	// Set the start point of the image we are using to (0,0)
	srcRect.x = srcRect.y = 0;
	destRect.x = x;
	destRect.y = y;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;

	// Leaving angle and center to be 0 
	SDL_RenderCopyEx(pRenderer,textureMap[id],&srcRect,&destRect,0,0,flip);
}

void textureManager::drawFrame(std::string id, int x, int y, int width, int height,  int currentRow, int currentFrame,
	                           SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
	SDL_Rect srcRect;
	SDL_Rect destRect;

	// Only difference to draw() function defined above is here
	// we are using currentFrame and currentRow to determine which
	// part of the sprite sheet we are using, i.e which picture we are drawing 
	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	///////////////////////
	destRect.x = x;
	destRect.y = y;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	SDL_RenderCopyEx(pRenderer,textureMap[id],&srcRect,&destRect,0,0,flip);
}


void textureManager::drawStatus(std::string heroID, std::string itemID, SDLGameObject* player, SDL_Renderer* pRenderer, TTF_Font* font, SDL_RendererFlip flip) {
	SDL_Color white = { 255, 255, 255 }; 
	// Level
	draw(heroID,32,27,32,32,pRenderer);
	stringstream ss1;
	ss1 << dynamic_cast<Player*>(player)->getLevel();
	string Level = "Level " + ss1.str();
	SDL_Surface* level = TTF_RenderText_Solid(font,Level.c_str(),white);
	SDL_Texture* texture_Level = SDL_CreateTextureFromSurface(pRenderer,level);
	// Render Level
	SDL_Rect destRect;
	destRect.x = 112;
	destRect.y = 35;
	destRect.h = level->h;
	destRect.w = level->w;
	SDL_RenderCopyEx(pRenderer,texture_Level,NULL,&destRect,0,0,SDL_FLIP_NONE);
    SDL_FreeSurface(level);
	SDL_DestroyTexture(texture_Level);

	// HP
	stringstream ss2;
	ss2 << dynamic_cast<Player*>(player)->getHP();
	string Hp = "HP      " + ss2.str();
	level = TTF_RenderText_Solid(font,Hp.c_str(),white);
	texture_Level = SDL_CreateTextureFromSurface(pRenderer,level);
	destRect.x = 33;
	destRect.y = 65;
	destRect.h = level->h;
	destRect.w = level->w;
	SDL_RenderCopyEx(pRenderer,texture_Level,NULL,&destRect,0,0,SDL_FLIP_NONE);
    SDL_FreeSurface(level);
	SDL_DestroyTexture(texture_Level);

	// Attack
	stringstream ss3;
	ss3 << dynamic_cast<Player*>(player)->getAttack();
	string Attack = "Attack   " + ss3.str();
	level = TTF_RenderText_Solid(font,Attack.c_str(),white);
	texture_Level = SDL_CreateTextureFromSurface(pRenderer,level);
	destRect.x = 33;
	destRect.y = 95;
	destRect.h = level->h;
	destRect.w = level->w;
	SDL_RenderCopyEx(pRenderer,texture_Level,NULL,&destRect,0,0,SDL_FLIP_NONE);
    SDL_FreeSurface(level);
	SDL_DestroyTexture(texture_Level);
	// Defence
	stringstream ss4;
	ss4 << dynamic_cast<Player*>(player)->getDefence();
	string Defence = "Defence  " + ss4.str();
	level = TTF_RenderText_Solid(font,Defence.c_str(),white);
	texture_Level = SDL_CreateTextureFromSurface(pRenderer,level);
	destRect.x = 33;
	destRect.y = 125;
	destRect.h = level->h;
	destRect.w = level->w;
	SDL_RenderCopyEx(pRenderer,texture_Level,NULL,&destRect,0,0,SDL_FLIP_NONE);
    SDL_FreeSurface(level);
	SDL_DestroyTexture(texture_Level);
	// Gold
	stringstream ss5;
	ss5 << dynamic_cast<Player*>(player)->getGold();
	string Gold = "gold     " + ss5.str();
	level = TTF_RenderText_Solid(font,Gold.c_str(),white);
	texture_Level = SDL_CreateTextureFromSurface(pRenderer,level);
	destRect.x = 33;
	destRect.y = 155;
	destRect.h = level->h;
	destRect.w = level->w;
	SDL_RenderCopyEx(pRenderer,texture_Level,NULL,&destRect,0,0,SDL_FLIP_NONE);
    SDL_FreeSurface(level);
	SDL_DestroyTexture(texture_Level);
	// Experience
	stringstream ss6;
	ss6 << dynamic_cast<Player*>(player)->getExperience();
	string Exp = "Exp      " + ss6.str();
	level = TTF_RenderText_Solid(font,Exp.c_str(),white);
	texture_Level = SDL_CreateTextureFromSurface(pRenderer,level);
	destRect.x = 33;
	destRect.y = 185;
	destRect.h = level->h;
	destRect.w = level->w;
	SDL_RenderCopyEx(pRenderer,texture_Level,NULL,&destRect,0,0,SDL_FLIP_NONE);
    SDL_FreeSurface(level);
	SDL_DestroyTexture(texture_Level);

    // Yellow Keys
	drawFrame(itemID,33,215,32,32,4,0,pRenderer);
	stringstream ss7;
	ss7 << dynamic_cast<Player*>(player)->getYellowKey();
	string Yellow = ss7.str();
	level = TTF_RenderText_Solid(font,Yellow.c_str(),white);
	texture_Level = SDL_CreateTextureFromSurface(pRenderer,level);
	destRect.x = 138;
	destRect.y = 215;
	destRect.h = level->h;
	destRect.w = level->w;
	SDL_RenderCopyEx(pRenderer,texture_Level,NULL,&destRect,0,0,SDL_FLIP_NONE);
    SDL_FreeSurface(level);
	SDL_DestroyTexture(texture_Level);

	// Red Key
	drawFrame(itemID,33,245,32,32,4,2,pRenderer);
	stringstream ss8;
	ss8 << dynamic_cast<Player*>(player)->getRedKey();
	string Red = ss8.str();
	level = TTF_RenderText_Solid(font,Red.c_str(),white);
	texture_Level = SDL_CreateTextureFromSurface(pRenderer,level);
	destRect.x = 138;
	destRect.y = 245;
	destRect.h = level->h;
	destRect.w = level->w;
	SDL_RenderCopyEx(pRenderer,texture_Level,NULL,&destRect,0,0,SDL_FLIP_NONE);
    SDL_FreeSurface(level);
	SDL_DestroyTexture(texture_Level);

	// Blue Key
	drawFrame(itemID,33,275,32,32,4,1,pRenderer);
	stringstream ss9;
	ss9 << dynamic_cast<Player*>(player)->getBlueKey();
	string Blue = ss9.str();
	level = TTF_RenderText_Solid(font,Blue.c_str(),white);
	texture_Level = SDL_CreateTextureFromSurface(pRenderer,level);
	destRect.x = 138;
	destRect.y = 275;
	destRect.h = level->h;
	destRect.w = level->w;
	SDL_RenderCopyEx(pRenderer,texture_Level,NULL,&destRect,0,0,SDL_FLIP_NONE);
    SDL_FreeSurface(level);
	SDL_DestroyTexture(texture_Level);
}


void textureManager::drawFight(std::string heroID, std::string enemyID, SDLGameObject* player, SDLGameObject* enemy, SDL_Renderer* pRenderer, TTF_Font* font, bool win, 
	                           int playerHP, int enemyHP, SDL_RendererFlip flip) {
	SDL_Color white = { 255, 255, 255 };
	SDL_Surface* level;
	SDL_Texture* texture_Level;
	SDL_Rect destRect;
	if(win) {
		stringstream ss1;
		stringstream ss2;
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
		draw(heroID,198,420,32,32,pRenderer);
		drawFrame(enemyID,294,420,32,32,enemy->getRow(),0,pRenderer);
		stringstream ss1;
		stringstream ss2;
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
    SDL_FreeSurface(level);
	SDL_DestroyTexture(texture_Level);
}

void textureManager::drawMessage(std::string messageType, int position, std::vector<SDLGameObject*> *things, SDL_Renderer* renderer, 
		             std::vector<std::vector<SDLGameObject*> >* background, Floor* floor, SDLGameObject* player, TTF_Font* font, int playerHP, int enemyHP) {
						 unsigned int lastTime = SDL_GetTicks();
						 if(messageType == "key" || messageType == "medicine" || messageType == "jewel") {
							 while(true) {
								unsigned int currentTime = SDL_GetTicks();
						  	    if(currentTime > lastTime + 500) {
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
									   SDL_Color white = { 255, 255, 255 };
	                                   SDL_Surface* level;
	                                   SDL_Texture* texture_Level;
	                                   SDL_Rect destRect;
									   string total;
									   if(messageType == "key"){
									       if((*things)[position]->getColor() == "yellow") {
		                                           total = "A yellow key gained.";
									       }
									       else if((*things)[position]->getColor() == "red") {
										           total = "A red key gained.";
									       } 
									       else {
										           total = "A blue key gained.";
									       }
									   }
									   else if(messageType == "medicine") {
										   if((*things)[position]->getColor() == "red") {
										           total = "50 HP recover.";
									       } 
										   else if((*things)[position]->getColor() == "blue") {
										           total = "100 HP recover.";
									       } 
										   else if((*things)[position]->getColor() == "green") {
										           total = "150 HP recover.";
									       } 
										   else if((*things)[position]->getColor() == "yellow") {
										           total = "200 HP recover.";
									       }
										   else {
											       
										   }
									   }
									   else {
										   if((*things)[position]->getColor() == "red") {
										           total = "3 points of attack increased.";
									       } 
										   else if((*things)[position]->getColor() == "blue") {
										           total = "2 points of defence increased.";
									       } 
										   else if((*things)[position]->getColor() == "green") {
										           total = "7 points of attack increased.";
									       } 
										   else if((*things)[position]->getColor() == "yellow") {
										           total = "5 points of defence increased.";
									       } 
										   else {
										   }
									   }
									   level = TTF_RenderText_Solid(font,total.c_str(),white); 
		                               texture_Level = SDL_CreateTextureFromSurface(renderer,level);
		                               destRect.x = 150;
	                                   destRect.y = 450;
	                                   destRect.h = level->h;
	                                   destRect.w = level->w;
									   SDL_RenderCopyEx(renderer,texture_Level,NULL,&destRect,0,0,SDL_FLIP_NONE);
	                                   SDL_RenderPresent(renderer);
									   SDL_FreeSurface(level);
	                                   SDL_DestroyTexture(texture_Level);
									   SDL_Event Event;
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

						 }
						 else {

						 }
}
void textureManager::changeFloor(SDL_Renderer* pRenderer, TTF_Font* font, int floor) {
	unsigned int lastTime = SDL_GetTicks();
	while(true) {
		unsigned int currentTime = SDL_GetTicks();
		if(currentTime > lastTime + 1000) {
				break;
		}
		else {
			SDL_RenderClear(pRenderer);
            SDL_Color white = { 255, 255, 255 };
	        SDL_Surface* level;
	        SDL_Texture* texture_Level;
	        SDL_Rect destRect;

			stringstream ss;
	        ss << floor;
	        string total = "Floor " + ss.str();
			level = TTF_RenderText_Solid(font,total.c_str(),white); 
		    texture_Level = SDL_CreateTextureFromSurface(pRenderer,level);
		    destRect.x = 260;
	        destRect.y = 288;
	        destRect.h = level->h;
	        destRect.w = level->w;
		    SDL_RenderCopyEx(pRenderer,texture_Level,NULL,&destRect,0,0,SDL_FLIP_NONE);
	        SDL_RenderPresent(pRenderer);
			SDL_FreeSurface(level);
	        SDL_DestroyTexture(texture_Level);
			SDL_Event Event;
		    while(SDL_PollEvent(&Event)){ }
		    }
	}
}
