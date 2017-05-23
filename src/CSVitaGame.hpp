#ifndef CSVITAGAME_HPP
#define CSVITAGAME_HPP

#include <vita2d.h>

#include "VitaPad.hpp"
#include "GameHttp.hpp"
#include "GameNetwork.hpp"
#include "GameEnums.hpp"
#include "MainMenu.hpp"
#include "MultiplayerLoginMenu.hpp"
#include "MultiplayerLobbyMenu.hpp"

class CSVitaGame{
	
	public:
		CSVitaGame();
		~CSVitaGame();
		void Start();
	private:
	
		MainMenu mainMenu;
		MultiplayerLoginMenu multiplayerLoginMenu;
		MultiplayerLobbyMenu multiplayerLobbyMenu;
		
		vita2d_pgf *pgf;
		std::string imageMenuBGPath = "app0:images/csmenubackground.png";;
		vita2d_texture *imageMenuBG;
		VitaPad vitaPad;
		GameHttp gameHttp;
		GameNetwork gameNetwork;
		ApplicationState applicationState = initstate;
		void GameLoop();
		
	
};


#endif