#ifndef MULTIPLAYERLOGINMENU_HPP
#define MULTIPLAYERLOGINMENU_HPP

#include <vita2d.h>
#include <psp2/types.h>

#include "VitaIME.hpp"
#include "GameEnums.hpp"
#include "GameHttp.hpp"

class MultiplayerLoginMenu{
	public:
		MultiplayerLoginMenu();
		MultiplayerLoginMenu(vita2d_pgf* &stdpgf);
		void passPGF(vita2d_pgf* &stdpgf);
		void passHTTP(GameHttp &gameHttpI);
		void moveInput(int x , int y); // 1 , 0 or -1 for x or y ( x = 1 => move to input to right )
		ApplicationState enter(); // return state
		ApplicationState back();  // return state
		void Draw();
		
		
		
	private:
		VitaIME vitaIME;
		GameHttp gameHttp;
	
		int selected_entry 	= 0;
		const int MAX_ENTRIES = 4;
		
		//int controlPosVerticalNumber[] 		= 	{ 0 , 1 , 2 , 2};
		//int controlPosHorizontalNumber[] 	= 	{ 0 , 0 , 0 , 1};
		
		vita2d_pgf *pgf;
		
		unsigned int selectedTextColor	;
		unsigned int normalTextColor 	;
		unsigned int selectedRectangleTextInputColor	;
		unsigned int normalRectangleTextInputColor 	;
	
	
		std::string username = "username";
		std::string password = "password";
		
		SceUInt waitMoveInput = 125000;
		SceUInt waitEnter = 250000;
		SceUInt waitBack = 250000;
	
};




#endif