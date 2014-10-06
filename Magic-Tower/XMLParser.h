#ifndef __XMLPARSER_H__
#define __XMLPARSER_H__
#include <iostream>
#include <vector>
#include "tinyxml.h"

class SDLGameObject;

class Parser {
public:
	static bool parseState( const char* stateFile, 
		                    std::string stateID,
                            std::vector<SDLGameObject*> *pObjects, 
						    std::vector<std::vector<SDLGameObject*> > *mObjects );

private:
	static void parseObjects( TiXmlElement* pStateRoot, 
		                      std::string stateID,
                              std::vector<SDLGameObject*> *pObjects, 
                              std::vector<std::vector<SDLGameObject*> > *mObjects );
};


#endif