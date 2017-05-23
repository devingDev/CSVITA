#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <vita2d.h>
#include <string>

#include "GameEnums.hpp"

class MainMenu{
	public:
		MainMenu();
		MainMenu(vita2d_pgf* &stdpgf);
		void passPGF(vita2d_pgf* &stdpgf);
		void moveInput(int x , int y); // 1 , 0 or -1 for x or y ( x = 1 => move to input to right )
		ApplicationState enter(); // return state
		ApplicationState back();  // return state
		void Draw();
		
		
		
	private:
		int selected_entry = 0;
		const int MAX_ENTRIES = 5;
		
		vita2d_pgf *pgf;
		std::string versionTextString = "undefinedversion";
		unsigned int selectedTextColor	;
		unsigned int normalTextColor 	;
	
	
		SceUInt waitMoveInput = 125000;
		SceUInt waitEnter = 250000;
		SceUInt waitBack = 250000;
		
		
};




#endif