/* 
   main.cpp

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

#include "Game.h"

int main(int argc, char* argv[]){
	if(!TheGame::Instance()->init("Magic Tower", 400,100,576,576,SDL_WINDOW_SHOWN)){
		TheGame::Instance()->gameover();
	}
	while(TheGame::Instance()->running()) {
		TheGame::Instance()->handleEvents();
		TheGame::Instance()->update();
		TheGame::Instance()->render();
	}
	TheGame::Instance()->clean();
	return 0;
}