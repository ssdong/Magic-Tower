#ifndef _GAME_H_
#define _GAME_H_

#include "SDL.h"
#include "SDL_ttf.h"
#include <vector>
#include <map>

class SDLGameObject;
class Player;
class Floor;

// The container of this game !

class Game {
public:
	~Game();
	static Game* Instance();
	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void render();
	void update();
	void handleEvents();
	void clean();
	bool running();
	void gameover();
	SDL_Renderer* getRenderer() const;

private:
	Game();
	static Game* instance;
	bool Running;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<std::vector<SDLGameObject*> >background;// Background
	SDLGameObject* player; // Game Player
	int currentFloor; // Currrent floor
	std::map<int, Floor*> floors; // Floors
	TTF_Font* font; // font !
};

typedef Game TheGame;

#endif 