/* Copyright (C) 2014   Susu Dong
   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely.
*/

/* This game is about the player find his or her way to the top floor. There is no time limit and player
   is designed not to die. However, if the player cannot make progress anymore and still find 
   himself or herself hanging around those alreday observed floors but cannot make it to new floor(because you 
   are still weaker than the enemies on the new floor), game is over !
   The key point is to use golds and experience carefully.
   Currently, the game is still under development where new floors and new elements are being added but it's successfully compiled.
   Check out www.youtube.com/watch?v=AI5IaBKRXtU&feature=youtu.be for a view. Thanks! :)
*/
#include "Game.h"

int main(int argc, char* argv[]){
	// Specify the window size and title and make it show up
	if(!TheGame::Instance()->init("Magic Tower", 400,100,576,576,SDL_WINDOW_SHOWN)){
		TheGame::Instance()->gameover();
	}
	// Running !
	while(TheGame::Instance()->running()) {
		TheGame::Instance()->handleEvents();
		TheGame::Instance()->update();
		TheGame::Instance()->render();
	}
	TheGame::Instance()->clean();
	return 0;
}