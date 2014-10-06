#ifndef __MEDICINE_H__ 
#define __MEDICINE_H__

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class LoaderParams;

/*
    There are currently 2 kinds of medicines
*/

class Medicine : public SDLGameObject {
public:
	Medicine();
	virtual ~Medicine();
	void load(const LoaderParams* param);
	void draw();
    void update();
	void clean();
	void setFrame(int newFrame);
	void setRow(int newRow);
};

class MedicineCreator : public BaseCreator {
public:
	 MedicineCreator();
	 ~MedicineCreator();
     SDLGameObject* createGameObject() const;

};

#endif