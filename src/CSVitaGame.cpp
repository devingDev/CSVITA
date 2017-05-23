
#include <vita2d.h>

#include "CSVitaGame.hpp"
#include "GameHttp.hpp"
#include "GameNetwork.hpp"
#include "GameEnums.hpp"
#include "MainMenu.hpp"
#include "MultiplayerLoginMenu.hpp"
#include "MultiplayerLobbyMenu.hpp"

CSVitaGame::CSVitaGame(){
	// ??
	
}

CSVitaGame::~CSVitaGame(){
	// maybe delete stuff 
	
	// finish vita2d (destroy)
	
}

void CSVitaGame::Start(){
	
	applicationState = initstate;
	
	// Init stuff
	// CTRL
	vitaPad.Read();
	// NET+HTTP (note : net socket does not need an extra init for sys module as NET module is loaded for http already!)
	gameHttp.Init();
	
	// vita2d
	vita2d_init();
	vita2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));
	pgf = vita2d_load_default_pgf();
	imageMenuBG = vita2d_load_PNG_file(imageMenuBGPath.c_str());
	
	mainMenu.passPGF(pgf);
	multiplayerLoginMenu.passPGF(pgf);
	multiplayerLoginMenu.passHTTP(gameHttp);
	multiplayerLobbyMenu.passPGF(pgf);
	multiplayerLobbyMenu.passHTTP(gameHttp);
	
	// set state and start loop
	applicationState = mainmenu;
	GameLoop();
	

	
	vita2d_fini();
	vita2d_free_texture(imageMenuBG);
	vita2d_free_pgf(pgf);
	
	//delete mainMenu;
	//delete multiplayerLobbyMenu;
	//delete multiplayerLoginMenu;
	//delete vitaPad;
	//delete gameHttp;
	//delete gameNetwork
}

int menuPressDX , menuPressDY;
bool menuPressEnter , menuPressBack;

void CSVitaGame::GameLoop(){
	

	while(applicationState != quit){
		
		// MENUs START
		if(applicationState != ingamesingle && applicationState != ingamemulti){
			vitaPad.Read();
			
			menuPressDX = menuPressDY = 0;
			menuPressEnter = menuPressBack = false;
			
			if(vitaPad.right){
				menuPressDX = 1;
			}else if(vitaPad.left){
				menuPressDX = -1;
			}else if(vitaPad.up){
				menuPressDY = -1;
			}else if(vitaPad.down){
				menuPressDY = 1;
			}
			
			if(vitaPad.cross){
				menuPressEnter = true;
			}else if(vitaPad.circle){
				menuPressBack = true;
			}
			
			vita2d_start_drawing();
			vita2d_clear_screen();
			
			if(applicationState == mainmenu){
				// MAINMENU
				mainMenu.moveInput(menuPressDX , menuPressDY);
				if(menuPressEnter)
					applicationState = mainMenu.enter();
				if(menuPressBack)
					applicationState = mainMenu.back();
				vita2d_draw_texture(imageMenuBG, 0 , 0 );
				mainMenu.Draw();
			}else if(applicationState == multiplayerloginmenu){
				// MULTIPLAYERLOGINMENU
				multiplayerLoginMenu.moveInput(menuPressDX , menuPressDY);
				if(menuPressEnter)
					applicationState = multiplayerLoginMenu.enter();
				if(menuPressBack)
					applicationState = multiplayerLoginMenu.back();
				vita2d_draw_texture(imageMenuBG, 0 , 0 );
				multiplayerLoginMenu.Draw();
			}else if(applicationState == multiplayerlobbymenu){
				//MULTIPLAYERLOBBYMENU
				multiplayerLobbyMenu.moveInput(menuPressDX , menuPressDY);
				if(menuPressEnter)
					applicationState = multiplayerLobbyMenu.enter();
				if(menuPressBack)
					applicationState = multiplayerLobbyMenu.back();
				vita2d_draw_texture(imageMenuBG, 0 , 0 );
				multiplayerLobbyMenu.Draw();
			}
			
			
			
			vita2d_end_drawing();
			vita2d_swap_buffers();
		}
		
		// MENU END
		
		// GAME START
		if(applicationState == ingamemulti){
			
		}else if(applicationState == ingamesingle){
			
		}
		
	}
	
	
	
}