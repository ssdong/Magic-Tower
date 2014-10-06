#ifndef __SDLGAMEOBJECT_H_
#define __SDLGAMEOBJECT_H_

#include "GameObject.h"
#include <string>

class LoaderParams;

class SDLGameObject : public GameObject {
public:
	SDLGameObject();
	
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void setFrame(int newFrame);
	virtual void setRow(int newRow);
	virtual void increaseX();
	virtual void increaseY();
	virtual void decreaseX();
	virtual void decreaseY();
	virtual void load(const LoaderParams* param);
	void setColor(std::string color);
	std::string getColor();
	virtual ~SDLGameObject();
	virtual int getX();
	virtual int getY();
	virtual int getRow();
	virtual int getFrame();

protected:
    int m_x;
	int m_y;

	int m_width;
	int m_height;

	int m_currentFrame;
	int m_currentRow;

	std::string m_textureID;

	std::string color;
};

#endif