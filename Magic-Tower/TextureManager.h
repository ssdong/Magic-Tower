#ifndef __TEXTMANAGER_H__
#define __TEXTMANAGER_H__
#include <map>
#include <string>
#include <vector>
#include "SDL.h"
#include "SDLGameObject.h"
#include "SDL_ttf.h"

class Floor;

class textureManager {
private:
	static textureManager* instan;
	textureManager();
public:
    ~textureManager();

	// Using singleton design pattern to ensure only one textureManager
    static textureManager* Instance();

	// Textures are stored together with its ID 
    std::map<std::string, SDL_Texture*> textureMap;

	// load
	// Notice fileName need to be transformed into C strings which is 
	// using .c_str() method
    bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

    // draw
	// x, y are the positions in the destination we want to draw to
	// height and width are the data about the image we are using
	// flip describes how the image should be displayed(e.g facing left or right)
    void draw(std::string id, int x, int y, int width, int height, 
	          SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	// drawFrame
	// Takes two more parameters
	// a) currentFrame we want to draw
	// b) which row it is in the sprite sheet
    void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame,
	               SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Draw the status of the player
	void drawStatus(std::string heroID, std::string itemID, SDLGameObject* player, SDL_Renderer* pRenderer, TTF_Font* font, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void drawFight(std::string heroID, std::string enemyID, SDLGameObject* player, SDLGameObject* enemy, SDL_Renderer* pRenderer, TTF_Font* font, bool win, int playerHP, int enemyHP, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void drawMessage(std::string messageType, int position, std::vector<SDLGameObject*> *things, SDL_Renderer* renderer, 
		             std::vector<std::vector<SDLGameObject*> >* background, Floor* floor, SDLGameObject* player, TTF_Font* font, int playerHP = 0, int enemyHP = 0);

	void changeFloor(SDL_Renderer* pRenderer, TTF_Font* font, int floor);
};

#endif