/* 
   XMLParser.cpp and XMLParser.h

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

#include "XMLParser.h"
#include "GameObjectFactory.h"
#include "LoaderParams.h"
#include <Windows.h>
#include "Tile.h"
#include "Stair.h"
#include "Enemy.h"
#include "Weapon.h"
using namespace std;

bool Parser::parseState(const char* stateFile, std::string stateID,
                        std::vector<SDLGameObject*> *pObjects, 
						std::vector<std::vector<SDLGameObject*> > *mObjects) {
     // First, Create XML document
	 TiXmlDocument xmlDoc;

	 // Load XML file and check if it fails
	 if(!xmlDoc.LoadFile(stateFile)) {
		 cerr << xmlDoc.ErrorDesc() << endl;
		 return false;
	 }
	 // Get the Root node
	 TiXmlElement* Root = xmlDoc.RootElement();

	 // Declare another Root node
	 TiXmlElement* anotherRoot = nullptr;


	 // Find the child whose ID matches the paramater ID(stateID). E.g I would like to find the 
	 // <Enemy> tag in .xml file, then I would pass "Enemy" into this function.
	 for(TiXmlElement* e = Root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		 if(e->Value() == stateID) {
			 anotherRoot = e;
		 }
	 }

	// Parse the nodes
	 if(stateID == "Map" || stateID == "Background" ) {
	    parseObjects(anotherRoot,stateID,nullptr,mObjects);
	 }
	 else {
		parseObjects(anotherRoot,stateID,pObjects,nullptr);
	 }
	 return true;
}


void Parser::parseObjects(TiXmlElement* pStateRoot,
	                      std::string stateID,
                          std::vector<SDLGameObject*> *pObjects,
						  std::vector<std::vector<SDLGameObject*> > *mObjects) {
	if(stateID == "Map" || stateID == "Background") {
     int i = 0;
		for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
			std::string m_lineID;
			std::string m_textureID;

			// Grab the Attributes
			m_lineID = e->Attribute("code");
			m_textureID = e->Attribute("textureID");
			
			std::vector<SDLGameObject*> temp;
            // Create the corresponding tiles and store it in the vector
			for(int j = 0; j < m_lineID.size(); j++) {
					SDLGameObject* instance = GameObjectFactory::Instance()->create(e->Attribute("type"));
					if(m_lineID[j] == 'A') {
					    LoaderParams* newLoader = new LoaderParams((192+j*32),(32+i*32),32,32,0,0,m_textureID);
						instance->load(newLoader);
						dynamic_cast<Tile*>(instance)->type = 'A';
					    delete newLoader;
					}
					else if(m_lineID[j] == 'B'){
						LoaderParams* newLoader = new LoaderParams((192+j*32),(32+i*32),32,32,1,0,m_textureID);
						instance->load(newLoader);
						dynamic_cast<Tile*>(instance)->type = 'B';
					    delete newLoader;
					}
					else {
						LoaderParams* newLoader = new LoaderParams((j*32),(i*32),32,32,0,0,m_textureID);
						instance->load(newLoader);
						dynamic_cast<Tile*>(instance)->type = 'C';
					    delete newLoader;
					}
					temp.push_back(instance);
			}
			++i;
			mObjects->push_back(temp);
		}
	}
	else {
		for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		 int m_x, m_y, m_width, m_height, m_currentFrame, m_currentRow, HP, Attack, Defence, Gold, Experience, number;
         std::string m_textureID;
		 std::string m_color;
		 std::string m_attribute;
		 

		 // Grab the Attributes !
		 e->Attribute("x_coord",&m_x);
		 e->Attribute("y_coord",&m_y);
		 e->Attribute("currentFrame",&m_currentFrame);
		 e->Attribute("currentRow",&m_currentRow);
		 e->Attribute("width",&m_width);
		 e->Attribute("height",&m_height);
		 m_textureID = e->Attribute("textureID");

		 if(stateID == "Medicine" || stateID == "Door" || stateID == "Key" || stateID == "Jewel") {
			 m_color = e->Attribute("color");
		 }
		 // Create the corresponding objects and store it in the vector
		 SDLGameObject* instance = GameObjectFactory::Instance()->create(e->Attribute("type"));
		 LoaderParams* newLoader = new LoaderParams(m_x*32, m_y*32, m_width, m_height,m_currentFrame,m_currentRow,m_textureID);
		 instance->load(newLoader);
		 if(stateID == "Weapon") {
			 m_attribute = e->Attribute("attribute");
			 if(m_attribute == "attack") {
				 dynamic_cast<Weapon*>(instance)->type = 'A';
				 e->Attribute("number", &number);
				 dynamic_cast<Weapon*>(instance)->num = number;
			 }
			 else if(m_attribute == "check") {
				 // TODO
			 }
			 else {
				 dynamic_cast<Weapon*>(instance)->type = 'D';
				 e->Attribute("number", &number);
				 dynamic_cast<Weapon*>(instance)->num = number;
			 }
		 }
		 if(stateID == "Enemy") {
			 e->Attribute("HP", &HP);
			 e->Attribute("Attack", &Attack);
			 e->Attribute("Defence", &Defence);
			 e->Attribute("Gold", &Gold);
			 e->Attribute("Experience", &Experience);
			 dynamic_cast<Enemy*>(instance)->setHP(HP);
			 dynamic_cast<Enemy*>(instance)->setAttack(Attack);
			 dynamic_cast<Enemy*>(instance)->setDefence(Defence);
			 dynamic_cast<Enemy*>(instance)->setGold(Gold);
			 dynamic_cast<Enemy*>(instance)->setExperience(Experience);
		 }
		 if(stateID == "Medicine" || stateID == "Door" || stateID == "Key" || stateID == "Jewel") {
			 instance->setColor(m_color);
		 }
		 if(stateID == "Stair") {
			 if(m_textureID == "up") {
				 dynamic_cast<Stair*>(instance)->type = 'U';
			 }
			 else {
				 dynamic_cast<Stair*>(instance)->type = 'D';
			 }
		 }
		 delete newLoader;
		 pObjects->push_back(instance);
	   }
	}
}