#ifndef __XMLPARSER_H__
#define __XMLPARSER_H__
#include <iostream>
#include <vector>
#include <unordered_map>
#include "tinyxml.h"

class Position;
class PositionHash;
class SDLGameObject;

class Parser {
public:
	static bool parseState( const char* stateFile, 
		                    std::string stateID,
                            std::unordered_map<Position, SDLGameObject*, PositionHash> *pObjects,
						    std::vector<std::vector<SDLGameObject*> > *mObjects );

private:
	static void parseObjects( TiXmlElement* pStateRoot, 
		                      std::string stateID,
                              std::unordered_map<Position, SDLGameObject*, PositionHash> *pObjects,
                              std::vector<std::vector<SDLGameObject*> > *mObjects );
};


#endif