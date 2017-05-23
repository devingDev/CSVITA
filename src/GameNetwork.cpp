#define VITASDK

#include <psp2/sysmodule.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/modulemgr.h> 

#include <psp2/net/net.h>
#include <psp2/net/netctl.h>

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#include "GameNetwork.hpp"
#include "Player.hpp"

GameNetwork::GameNetwork(){
	
}

GameNetwork::~GameNetwork(){
	
	leftServer = true;
	
}





//void *UdpConnectAndTestPackets(void *threadid);

void GameNetwork::werror(std::string msg) {
	//sceKernelDelayThread(2*1000000);
    //exit(0);
}

void GameNetwork::startPthreadNetwork(std::string ipS , int portS , unsigned char xCal , unsigned char yCal){
	
	lastResponse = "";
	ServerIpString 	= 	ipS;
	ServerPort 		=	portS;
	//ServerIpString 	= 	SRV_IPO;
	//ServerPort 		= 	PORTO;
	
	sceSysmoduleLoadModule(SCE_SYSMODULE_NET);
	SceNetInitParam netInitParam;
	int size = 2*1024*1024;
	netInitParam.memory = malloc(size);
	netInitParam.size = size;
	netInitParam.flags = 0;
	sceNetInit(&netInitParam);
	sceNetCtlInit();
	
	//UdpConnectAndTestPacketsU();
	
	localplayer = Player(xCal , yCal);
	
	for(int pl = 0; pl < MAX_PLAYERS ; pl++){
		players[pl] = Player(0,0);
	}
	
	// v crashing somewhere
	pthreadrc = pthread_create(&_thread, NULL, &GameNetwork::pthreadUDPHelper, this);
}

void *GameNetwork::UdpConnectAndTestPackets() {
	
	
	
	// SOCKET and n 
	int sockfd ,  n;
	//int portno;
    socklen_t serverlen;
    struct sockaddr_in serveraddr;
    struct hostent *server;
    //char * hostname = new char[ServerIpString.size() + 1];
    char buf[BUFSIZE];
	
	//hostname = ServerIpString.c_str();
	//std::copy(ServerIpString.begin() , ServerIpString.end() , hostname);
	//hostname[ServerIpString.size()] = '\0';
	//portno = ServerPort;
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
        werror("ERROR opening socket");
		pthread_exit(NULL);
	}
	
	server = gethostbyname(ServerIpString.c_str());
    if (server == NULL) {
        sceKernelDelayThread(2*1000000);
		pthread_exit(NULL);
    }
	
	bzero((char *) &serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serveraddr.sin_addr.s_addr, server->h_length);
    serveraddr.sin_port = htons(ServerPort);
	
	
	serverlen = sizeof(serveraddr);
	
	int playerID = 0;
	
	lastResponse = "Connecting wait for response..";
	
	leftServer = false;
	
	while(!leftServer){
		
		bzero(buf, BUFSIZE);
		strcpy(buf , "CONNECTJohn:Password");
		n = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&serveraddr, serverlen);
		if (n < 0) 
		  werror("ERROR in sendto");
		
		bzero(buf, BUFSIZE);
		
		n = recvfrom(sockfd, buf, BUFSIZE, 0, (struct sockaddr*)&serveraddr, &serverlen);
		if (n < 0) 
		  werror("ERROR in recvfrom");
	  
		if(n > 0){
			buf[n] = '\0';
			lastResponse = buf;
			//lastResponse = std::string(buf , n);
		  
			if(buf[0] == 'R'){
				playerID = buf[1] - '0';
				break;
			}
		}
	
		sceKernelDelayThread(1*1000*500);
	}
	
	std::string sendNext;
	while (!leftServer){
		
		sendNext = "SENDDATA" + std::to_string(playerID) + ":" + localplayer.getPosString();
		bzero(buf, BUFSIZE);
		strcpy(buf , sendNext.c_str());
		n = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&serveraddr, serverlen);
		if (n < 0) 
		  werror("ERROR in sendto");
	  
	  
		bzero(buf, BUFSIZE);
		
		n = recvfrom(sockfd, buf, BUFSIZE, 0, (struct sockaddr*)&serveraddr, &serverlen);
		if (n < 0) 
		  werror("ERROR in recvfrom");
	  
		if(n> 0){
			buf[n] = '\0';
			lastResponse = buf;
			lastResponse = "";
			if(buf[0] == 'G'){
				/*
							bufstr = "G";
							for(int pl = 0 ; pl < playerAmount ; pl ++){
									bufstr += "#" + players[pl].GetPosition();
							}
							bufstr += ":TIME#ROUND";
				
						G#12P20.232P30.23#1.2P9.2:TIME#ROUND
						G#20D99.0D99.0:TIME#ROUND;  			!!!!!!!!!!!!!!!!!!!!!!!! D MEANS DISCONNECTED , P if he is still connected ( to parse it :) )
						G#20P99.0P99.0#23P99.0P99.0:TIME#ROUND;
						G#0P854.945984P101.664818#1P200.512100P200.041229:TIME#ROUND
				*/
				bool isPlayerData = false;
				bool isPlayerID = false;
				bool isPlayerX = false;
				bool isPlayerY = false;
				bool isGameData = false;
				bool isDC = false;
				std::string pos = "";
				int playerNum = 0;
				char curr = 'x';
				float xFPos , yFPos;
				int currPid = 0;
				for(int sD = 0; sD < n ; sD++){
					curr = buf[sD];
					if(curr=='#' && !isPlayerData && !isGameData){
						isPlayerData = true;
						isPlayerID = true;
						isPlayerX = false;
						isPlayerY = false;
						isDC = false;
						pos = "";
					}else if(curr=='P' && isPlayerData && isPlayerID){
						
						// COPY STRING TO PLAYERID
						lastResponse += "P ID: " + pos;
						currPid = atoi(pos.c_str());
						isDC = false;
						isPlayerID = false;
						isPlayerX = true;
						isPlayerY = false;
						pos = "";
					}else if(curr=='D' && isPlayerData && isPlayerID){
						
						// COPY STRING TO PLAYERID
						lastResponse += "D ID: " + pos;
						currPid = atoi(pos.c_str());
						isDC = true;
						isPlayerID = false;
						isPlayerX = true;
						isPlayerY = false;
						pos = "";
					}else if(curr=='P' && isPlayerData && !isPlayerID && isPlayerX){
						
						// COPY STRING TO PLAYERXFPOS
						lastResponse += "P x: " + pos;
						xFPos = atof(pos.c_str());
						isDC = false;
						isPlayerID = false;
						isPlayerX = false;
						isPlayerY = true;
						pos = "";
					}else if(curr=='D' && isPlayerData && !isPlayerID && isPlayerX){
						
						// COPY STRING TO PLAYERXFPOS
						lastResponse += "D x: " + pos;
						xFPos = atof(pos.c_str());
						isDC = true;
						isPlayerID = false;
						isPlayerX = false;
						isPlayerY = true;
						pos = "";
					}else if(curr=='#' && isPlayerData && !isPlayerID && !isPlayerX && isPlayerY){
						
						// COPY STRING TO PLAYERYFPOS
						lastResponse += "P y: " + pos;
						yFPos = atof(pos.c_str());
						
						if(currPid == playerID){
							
						}else{
							if(isDC){
								players[currPid].SetPositionNetwork(-99999 , -99999);
								players[currPid].inServer = false;
							}else{
								players[currPid].SetPositionNetwork(xFPos , yFPos);
								players[currPid].inServer = true;
							}
							
							playerNum++;
						}
						
						
						isPlayerID = true;
						isPlayerX = false;
						isPlayerY = false;
						isDC = false;
						currPid = 0;
						pos = "";
					}else if(curr==':' && isPlayerData && !isGameData){
						
						// COPY STRING TO PLAYERYFPOS
						lastResponse += "P y: " + pos;
						yFPos = atof(pos.c_str());
						
						if(currPid == playerID){
							
						}else{
							if(isDC){
								players[currPid].SetPositionNetwork(-99999 , -99999);
								players[currPid].inServer = false;
							}else{
								players[currPid].SetPositionNetwork(xFPos , yFPos);
								players[currPid].inServer = true;
							}
							
							playerNum++;
						}
						
						
						isPlayerData = false;
						isPlayerID = false;
						isPlayerX = false;
						isPlayerY = false;
						isDC = false;
						currPid = 0;
						isGameData = true;
						pos = "";
					}else if(isPlayerID){
						pos += curr;
					}else if(isPlayerX){
						pos += curr;
					}else if(isPlayerY){
						pos += curr;
					}else if(isGameData){
						break;
					}
					
					
					
					
					
					/*
					if(curr=='#' && !isGameData && isPlayerY){
						yFPos = atof(pos.c_str());
						players[playerNum].SetPositionNetwork(xFPos , yFPos);
						playerNum++;
						isPlayerX = false;
						isPlayerY = false;
						currPid = -1;
					}
					
					if(curr=='#' && !isGameData){
						isPlayerData = true;
						isPlayerID = true;
						pos = "";
					}else if(curr=='#' && !isGameData && isPlayerID){
						isPlayerData = true;
						isPlayerID = false:
						isPlayerX = true;
						pos = "";
					}else if(curr==':'){
						isPlayerData = false;
						isGameData = true;
					}else if(isPlayerData){
						if(curr=='D'){
							xFPos = atof(pos.c_str());
							isPlayerY = true;
							pos = "";
						}else if(curr=='P'){
							xFPos = atof(pos.c_str());
							isPlayerY = true;
							pos = "";
						}else if(isPlayerID){
							pos += curr;
						}else if(isPlayerX){
							pos += curr;
						}else if(isPlayerY){
							pos+= curr;
						}
						
					}else if(isGameData){
						
					}*/
					
					
					
				}
			}
			
		}

		sceKernelDelayThread(1*1000); // 1 ms
	}
	
	
	close(sockfd);
	
	sceKernelDelayThread(1*500000);
	
   
	pthread_exit(NULL);
	
	// NOT SURE IF THIS SHOULD RETURN NULL OR SOMETHING ELSE ORRRR NOTHING AT ALL (works if nothing returned ) !!
	return NULL;
}
