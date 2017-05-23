

#include "VitaIME.hpp"
#include "MultiplayerLoginMenu.hpp"
#include "GameHttp.hpp"
#include "GameEnums.hpp"
#include "version.h"

#include <psp2/kernel/threadmgr.h> 
#include <psp2/display.h>
#include <vita2d.h>

#include <cstring>
#include <string>



MultiplayerLoginMenu::MultiplayerLoginMenu(){
	
	selectedTextColor 	= RGBA8(0xFF , 0xFF , 0xFF , 0xFF);
	normalTextColor 	= RGBA8(0x44 , 0x44 , 0x44 , 0xFF);
	selectedRectangleTextInputColor = RGBA8(0x33 , 0x33 , 0x33 , 0x4F);
	normalRectangleTextInputColor = RGBA8(0x00 , 0x00 , 0x00 , 0x4F);
	
}

MultiplayerLoginMenu::MultiplayerLoginMenu(vita2d_pgf* &stdpgf){
	pgf = stdpgf;
	MultiplayerLoginMenu();
}

void MultiplayerLoginMenu::passPGF(vita2d_pgf* &stdpgf){
	pgf = stdpgf;
}

void MultiplayerLoginMenu::passHTTP(GameHttp &gameHttpI){
	gameHttp = gameHttpI;
}

void MultiplayerLoginMenu::moveInput(int x , int y){
	selected_entry += y;
	if(selected_entry >= MAX_ENTRIES)
		selected_entry = 0;
	if(selected_entry < 0)
		selected_entry = MAX_ENTRIES - 1;
	
	
	sceKernelDelayThread(waitMoveInput);

}

ApplicationState MultiplayerLoginMenu::enter(){
	
	ApplicationState s = multiplayerloginmenu;
	
	if(selected_entry == 0){
		//char usernameChars[512];
		//strncpy(usernameChars, username.c_str(), sizeof(usernameChars));
		//usernameChars[sizeof(usernameChars) - 1] = 0;
		vita2d_end_drawing();
		vita2d_swap_buffers();
		username = vitaIME.getUserText("Username :" , username.c_str());
		vita2d_start_drawing();
		vita2d_clear_screen();
	}else if(selected_entry == 1){
		//char passwordChars[512];
		//strncpy(passwordChars, password.c_str(), sizeof(passwordChars));
		//passwordChars[sizeof(passwordChars) - 1] = 0;
		vita2d_end_drawing();
		vita2d_swap_buffers();
		password = vitaIME.getUserText("Password :" , password.c_str());
		vita2d_start_drawing();
		vita2d_clear_screen();
	}else if(selected_entry == 2){
		// login
		if(gameHttp.loginUser(username ,  password) == 1){
			s = multiplayerlobbymenu;
		}else{
			username = "Failed to login!";
		}
	}else if(selected_entry == 3){
		// register
		if(gameHttp.registerUser(username ,  password) == 1){
			s = multiplayerlobbymenu;
		}else{
			username = "Failed to register!";
		}
	}
	
	sceKernelDelayThread(waitEnter);
	
	return s;
}

ApplicationState MultiplayerLoginMenu::back(){
	ApplicationState s = mainmenu;
	
	
	sceKernelDelayThread(waitBack);
	
	return s;
}

void MultiplayerLoginMenu::Draw(){
	
	vita2d_pgf_draw_textf(pgf, 64, 64, normalTextColor, 1.25f, "Multiplayer , write your stuff and press either login or register !" );
	
	if(selected_entry == 0){
		vita2d_draw_rectangle(320 , 250 , 320 , 48 , selectedRectangleTextInputColor);
		//vita2d_pgf_draw_textf(pgf, 670, 280, selectedTextColor, 1.25f, "Username" );
		vita2d_pgf_draw_textf(pgf, 320, 280, selectedTextColor, 1.25f, username.c_str() );
	}else{
		vita2d_draw_rectangle(320 , 250 , 320 , 48 , normalRectangleTextInputColor);
		//vita2d_pgf_draw_textf(pgf, 670, 280, normalTextColor, 1.25f, "Username" );
		vita2d_pgf_draw_textf(pgf, 320, 280, normalTextColor, 1.25f, username.c_str() );
	}
	if(selected_entry == 1){
		vita2d_draw_rectangle(320 , 300 , 320 , 48 , selectedRectangleTextInputColor);
		//vita2d_pgf_draw_textf(pgf, 670, 330, selectedTextColor, 1.25f, "Password" );
		vita2d_pgf_draw_textf(pgf, 320, 330, selectedTextColor, 1.25f, password.c_str() );
	}else{
		vita2d_draw_rectangle(320 , 300 , 320 , 48 , normalRectangleTextInputColor);
		//vita2d_pgf_draw_textf(pgf, 670, 330, normalTextColor, 1.25f, "Password" );
		vita2d_pgf_draw_textf(pgf, 320, 330, normalTextColor, 1.25f, password.c_str() );
	}
	
	
	if(selected_entry == 2){
		vita2d_pgf_draw_textf(pgf, 350, 400, selectedTextColor, 1.25f, "Login!");
	}else{
		vita2d_pgf_draw_textf(pgf, 350, 400, normalTextColor, 1.25f, "Login!");
	}
	if(selected_entry == 3){
		vita2d_pgf_draw_textf(pgf, 500, 400, selectedTextColor, 1.25f, "Register!" );
	}else{
		vita2d_pgf_draw_textf(pgf, 500, 400, normalTextColor, 1.25f, "Register!" );
	}
	
	
	
	
	
	
}
		

