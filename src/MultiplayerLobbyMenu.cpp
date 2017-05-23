

#include <psp2/display.h>
#include <vita2d.h>
#include <psp2/types.h>
#include <psp2/kernel/threadmgr.h> 
#include "MultiplayerLobbyMenu.hpp"
#include <string>
#include "json.hpp"




MultiplayerLobbyMenu::MultiplayerLobbyMenu(){
	refreshServerList = true;
	selectedTextColor 	= RGBA8(0xFF , 0xFF , 0xFF , 0xFF);
	normalTextColor 	= RGBA8(0x44 , 0x44 , 0x44 , 0xFF);
	selectedRectangleTextInputColor = RGBA8(0x33 , 0x33 , 0x33 , 0x4F);
	normalRectangleTextInputColor = RGBA8(0x00 , 0x00 , 0x00 , 0x4F);
	
}

MultiplayerLobbyMenu::MultiplayerLobbyMenu(vita2d_pgf* &stdpgf){
	pgf = stdpgf;
	MultiplayerLobbyMenu();
}

void MultiplayerLobbyMenu::passPGF(vita2d_pgf* &stdpgf){
	pgf = stdpgf;
}

void MultiplayerLobbyMenu::passHTTP(GameHttp &gameHttpI){
	gameHttp = gameHttpI;
}


void MultiplayerLobbyMenu::moveInput(int x , int y){
	selected_entry += y;
	if(selected_entry >= server_amount)
		selected_entry = 0;
	if(selected_entry < 0)
		selected_entry = server_amount - 1;
	
	
	sceKernelDelayThread(waitMoveInput);

}

void MultiplayerLobbyMenu::joinServer(){
	
}

ApplicationState MultiplayerLobbyMenu::enter(){
	
	ApplicationState s = multiplayerlobbymenu;
	
	if(server_amount > 0){
		joinServer();
	}
	
	sceKernelDelayThread(waitEnter);
	
	return s;
}

ApplicationState MultiplayerLobbyMenu::back(){
	ApplicationState s = mainmenu;
	
	
	sceKernelDelayThread(waitBack);
	
	return s;
}

void MultiplayerLobbyMenu::Draw(){
	
	if(refreshServerList){
		serverslisttext = gameHttp.getServerlistJSON();
		refreshServerList = false;
		
		nlohmann::json j_complete = nlohmann::json::parse(serverslisttext);
		server_amount = j_complete["amount"].get<int>();
		
		
		for(int s = 0 ; s < server_amount ; s++){
		
		serverNames[s] = j_complete["servers"][s]["servername"].get<std::string>();
		serverIps[s] = j_complete["servers"][s]["ip"].get<std::string>();
		serverPorts[s] = j_complete["servers"][s]["port"].get<int>();
		serverMaxplayers[s] = j_complete["servers"][s]["maxplayers"].get<int>();
		serverCurrentPlayers[s] = j_complete["servers"][s]["players"].get<int>();
		serverShowString[s] = serverNames[s] + " " ;
		serverShowString[s] += serverIps[s] + " " + std::to_string(serverPorts[s]) + " ";
		serverShowString[s] += std::to_string(serverCurrentPlayers[s]) + " " + std::to_string(serverMaxplayers[s]);
	}
		
	}
	
	if(server_amount <= 0){
		vita2d_pgf_draw_textf(pgf, 64, 64, normalTextColor, 1.25f, "No Servers found!" );
	}else{
		for(int i = 0; i < server_amount; i++){
			if(selected_entry == i){
				vita2d_pgf_draw_textf(pgf, 64, 64, selectedTextColor, 1.25f, serverShowString[i].c_str() );
			}else{
				vita2d_pgf_draw_textf(pgf, 64, 64, normalTextColor, 1.25f, serverShowString[i].c_str() );
			}
			
		}
	}
	


}


	

