#ifndef NETWORK_H
#define NETWORK_H


#include <pthread.h>
#include <string>

#include "Player.hpp"


#define INADDR_ANY ((unsigned long int) 0x00000000)
#define NET_INIT_SIZE 1*1024*1024
#define PORTO 50000
#define BUFSIZE 8192
#define SRV_IPO "37.120.174.141"
#define printf psvDebugScreenPrintf
#define NET_SIZE       0x100000 
#define MAX_PLAYERS 32

class GameNetwork{

	public:
		GameNetwork();
		~GameNetwork();
		Player players[MAX_PLAYERS];
		Player localplayer;
		std::string lastResponse;
		void * UdpConnectAndTestPackets();
		void * UdpConnectAndTestPacketsU();
		void werror(std::string msg);
		void startPthreadNetwork(std::string ip , int port , unsigned char xCal , unsigned char yCal);
		pthread_t getHandle() const { return _thread; };
		static void *pthreadUDPHelper(void *context)
		{
			return ((GameNetwork *)context)->UdpConnectAndTestPackets();
		}

	private:
		bool leftServer;
		std::string ServerIpString;
		int ServerPort;
		pthread_t _thread;
		int pthreadrc;

};



#endif