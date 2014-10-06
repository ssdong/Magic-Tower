#ifndef __LOADERPARAMS_H__
#define __LOADERPARAMS_H__
#include <string>

// This class stores loading data
class LoaderParams{
public:
     LoaderParams(int x, int y, int width, int height, int currentFrame, int currentRow,std::string textureID) 
		 :m_x(x), m_y(y), m_width(width), m_height(height),m_currentFrame(currentFrame),m_currentRow(currentRow),m_textureID(textureID){}
     int getX() const { return m_x; }
     int getY() const { return m_y; }
     int getWidth() const { return m_width; }
     int getHeight() const { return m_height; }
	 int getFrame() const { return m_currentFrame; }
	 int getRow() const { return m_currentRow; }
     std::string getID() const { return m_textureID; }

private:
     int m_x; // x position on the screen
     int m_y;  // y position on the screen
     int m_width; // picture size
     int m_height; // picture size
	 int m_currentFrame; 
	 int m_currentRow;
     std::string m_textureID; // the sprite sheet ID 
};


#endif