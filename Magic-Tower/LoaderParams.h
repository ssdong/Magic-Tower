#ifndef __LOADERPARAMS_H__
#define __LOADERPARAMS_H__
#include <string>

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
     int m_x;
     int m_y;
     int m_width;
     int m_height;
	 int m_currentFrame;
	 int m_currentRow;
     std::string m_textureID;
};


#endif