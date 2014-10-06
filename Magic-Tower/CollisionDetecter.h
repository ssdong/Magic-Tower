#ifndef __COLLISIONDETECTOR_H__
#define __COLLISIONDETECTOR_H__
#include <vector>
#include "SDL.h"
#include "SDL_ttf.h"

/*
   Collision detector deals with various collision events to
   make player interact with elements(e.g NPC, items etc)
*/

class SDLGameObject;

class Collision {
private:
    static Collision* instance;
    Collision();

public:
    ~Collision();
    static Collision* Instance();

    // Check if the collision is a key
    bool detectKey( std::vector<SDLGameObject* >* keys, 
                    SDLGameObject* player, 
                    char direction, 
                    int offset, 
                    int& position );

    // Check if the collision is a jewel
    bool detectJewel( std::vector<SDLGameObject* >* jewels, 
                      SDLGameObject* player, 
                      char direction, 
                      int offset, 
                      int& position );

    // Check if the collision is a medicine
    bool detectMedicine( std::vector<SDLGameObject* >* medicines, 
                         SDLGameObject* player, 
                         char direction, 
                         int offset, 
                         int& position );

    // Check if a door exists in order to prepare for an animation of door open
    bool detectDoorExist( std::vector<SDLGameObject* >* doors, 
                          SDLGameObject* player, 
                          char direction, 
                          int offset, 
                          int& position );

    // Check if the player hold enough key to open the door of certain color
    bool detectDoor( std::vector<SDLGameObject* >* doors, 
                     SDLGameObject* player, 
                     char direction, 
                     int offset, 
                     int position );

    // Check if an enemy exists in order to prepare for an animation of fight
    bool detectEnemyExist( std::vector<SDLGameObject* >* enemies, 
                           SDLGameObject* player, 
                           char direction,
                           int offset, 
                           int& position );

    // Calculate if the player can defeat the enemy or not to decide whether the animation is going to be on or not
    bool detectCanFightWithEnemy( std::vector<SDLGameObject* >* enemies, 
                                  SDLGameObject* player, 
                                  char direction, 
                                  int offset, 
                                  int position );

    // Fight !!!! 
    bool fight( std::vector<SDLGameObject* >* enemies, 
                SDLGameObject* player, 
                char direction, 
                int offset, 
                int position, 
                SDL_Renderer* pRenderer, 
                TTF_Font* font, 
                int &playerHP, 
                int &enemyHP, 
                int P_E_damage, 
                int E_P_damage, 
                unsigned int &lastTime );

    // Check if the player is crashing the wall
    bool detectWall( std::vector<std::vector<SDLGameObject*> > *map, 
                     SDLGameObject* player, 
                     char direction, 
                     int offset );

    // Check if the player is trying to go upstairs or downstairs
    bool detectStair( std::vector<SDLGameObject* >* stairs, 
                      SDLGameObject* player, 
                      char direction, 
                      int offset, 
                      char& stairType );
};

#endif