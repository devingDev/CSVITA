


#include "MainMenu.hpp"
#include "GameEnums.hpp"
#include "version.h"

#include <psp2/display.h>
#include <vita2d.h>
#include <psp2/types.h>
#include <psp2/kernel/threadmgr.h> 

#include <string>



MainMenu::MainMenu(){
	versionTextString = DEFINED_VERSION;
	selectedTextColor 	= RGBA8(0xFF , 0xFF , 0xFF , 0xFF);
	normalTextColor 	= RGBA8(0x44 , 0x44 , 0x44 , 0xFF);
	
}

MainMenu::MainMenu(vita2d_pgf* &stdpgf){
	pgf = stdpgf;
	MainMenu();
}

void MainMenu::passPGF(vita2d_pgf* &stdpgf){
	pgf = stdpgf;
}

void MainMenu::moveInput(int x , int y){
	selected_entry += y;
	if(selected_entry >= MAX_ENTRIES)
		selected_entry = 0;
	if(selected_entry < 0)
		selected_entry = MAX_ENTRIES - 1;
	
	sceKernelDelayThread(waitMoveInput);


}

ApplicationState MainMenu::enter(){
	
	ApplicationState s = mainmenu;
	
	if(selected_entry == 4){
		s = quit;
	}else if(selected_entry == 1){
		s = multiplayerloginmenu;
	}
	
	sceKernelDelayThread(waitEnter);
	
	return s;
}

ApplicationState MainMenu::back(){
	ApplicationState s = mainmenu;
	sceKernelDelayThread(waitBack);
	return s;
}

void MainMenu::Draw(){
	
	vita2d_pgf_draw_textf(pgf, 64, 64, normalTextColor, 1.25f, versionTextString.c_str() );
	
	if(selected_entry == 0){
		vita2d_pgf_draw_textf(pgf, 750, 392, selectedTextColor, 1.5f, "Singleplayer" );
	}else{
		vita2d_pgf_draw_textf(pgf, 750, 392, normalTextColor, 1.5f, "Singleplayer" );
	}
	if(selected_entry == 1){
		vita2d_pgf_draw_textf(pgf, 750, 422, selectedTextColor, 1.5f, "Multiplayer" );
	}else{
		vita2d_pgf_draw_textf(pgf, 750, 422, normalTextColor, 1.5f, "Multiplayer" );
	}
	if(selected_entry == 2){
		vita2d_pgf_draw_textf(pgf, 750, 452, selectedTextColor, 1.5f, "Settings");
	}else{
		vita2d_pgf_draw_textf(pgf, 750, 452, normalTextColor, 1.5f, "Settings");
	}
	if(selected_entry == 3){
		vita2d_pgf_draw_textf(pgf, 750, 482, selectedTextColor, 1.5f, "Credits" );
	}else{
		vita2d_pgf_draw_textf(pgf, 750, 482, normalTextColor, 1.5f, "Credits" );
	}
	if(selected_entry == 4){
		vita2d_pgf_draw_textf(pgf, 750, 512, selectedTextColor, 1.5f, "Exit" );
	}else{
		vita2d_pgf_draw_textf(pgf, 750, 512, normalTextColor, 1.5f, "Exit" );
	}
	
	
	
	
	
	
}
		

