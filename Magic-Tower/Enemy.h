#ifndef __ENEMY_H__ 
#define __ENEMY_H__

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class LoaderParams;
class Player;

class Enemy : public SDLGameObject {
private:
	int HP;
	int attack;
	int defence;
	int gold;
	int experience;

public:
	Enemy();
	virtual ~Enemy();
	void load(const LoaderParams* param);
	void draw();
    void update();
	void clean();
	bool collideHelper(int &playerHP, int &enemyHP, int P_E_damage, int E_P_damage,unsigned int& lastTime);
	bool canFight(Player* player);
	void collide(SDLGameObject* player);
	void setFrame(int newFrame);
	void setRow(int newRow);
	void setHP(int hp);
	void setAttack(int attack);
	void setDefence(int defence);
	void setGold(int gold);
	void setExperience(int experience);
	int getHP();
	int getAttack();
	int getDefence();
	int getGold();
	int getExperience();
};

class EnemyCreator : public BaseCreator {
public:
	 EnemyCreator();
	 ~EnemyCreator();
     SDLGameObject* createGameObject() const;

};

#endif