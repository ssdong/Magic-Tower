#ifndef __PLAYER_H__ 
#define __PLAYER_H__

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class LoaderParams;

class Player : public SDLGameObject {
private:
	int level;
	int HP;
	int attack;
	int defence;
	int gold;
	int experience;
	int yellowKey;
	int redKey;
	int blueKey;
	bool canOpenGreenDoor;
public:
	Player(/*int level = 1, int HP = 1000, int Attack = 10, int Defence = 10, int gold = 0, int experience = 0, int yellow = 0
		   , int red = 0, int blue = 0*/);
	virtual ~Player();
	void load(const LoaderParams* param);
	void draw();
    void update();
	void clean();
	void setFrame(int newFrame);
	void setRow(int newRow);
	void increaseX();
	void increaseY();
	void decreaseX();
	void decreaseY();
	int getLevel();
	int getHP();
	int getAttack();
	int getDefence();
	int getGold();
	int getExperience();
	int getYellowKey();
	int getRedKey();
	int getBlueKey();
	bool getGreenDoor();
	void setX(int x);
	void setY(int y);
	void setGreenDoor();
	bool setLevel(int level);
	bool setHP(int hp);
	bool setAttack(int attack);
	bool setDefence(int defence);
	bool setGold(int gold);
	bool setExperience(int experience);
	bool setYellowKey(int key);
	bool setBlueKey(int key);
	bool setRedKey(int key);
};

class PlayerCreator : public BaseCreator {
public:
     SDLGameObject* createGameObject() const;
};

#endif