#ifndef MULTIPLAYERLOBBYMENU_HPP
#define MULTIPLAYERLOBBYMENU_HPP

#include <vita2d.h>
#include <psp2/types.h>
#include "GameEnums.hpp"
#include "GameHttp.hpp"

#include <string>


class MultiplayerLobbyMenu{
	public:
		MultiplayerLobbyMenu();
		MultiplayerLobbyMenu(vita2d_pgf* &stdpgf);
		void passPGF(vita2d_pgf* &stdpgf);
		void passHTTP(GameHttp &gameHttpI);
		void moveInput(int x , int y); // 1 , 0 or -1 for x or y ( x = 1 => move to input to right )
		ApplicationState enter(); // return state
		ApplicationState back();  // return state
		void Draw();
		
		
		
	private:
		void joinServer();
	
		bool refreshServerList;
		GameHttp gameHttp;
		int selected_entry 	= 0;
		int server_amount = 1;
		
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
		
		std::string ip = "37.120.174.141";
		int port = 50000;
	
		std::string serverslisttext;
		
		std::string serverNames[64], serverIps[64] , serverShowString[64] ;
		int serverPorts[64] , serverMaxplayers[64] , serverCurrentPlayers[64];
		
};




#endif