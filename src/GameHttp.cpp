#include <psp2/sysmodule.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/net/net.h>
#include <psp2/net/netctl.h>
#include <psp2/net/http.h>
#include <debugnet.h>

#include <string>
#include <stdlib.h>
#include <string.h>


#include "GameHttp.hpp"

GameHttp::GameHttp(){
	lastResponse = "";
}

GameHttp::GameHttp(bool dontInitialize){
	lastResponse = "";
	initializedHttp = true;
}

GameHttp::~GameHttp(){
	lastResponse = "";
	
	if(initializedHttp){
		netAndHttpTerm();
	}
}

void GameHttp::Init(){
	
	if(!initializedHttp){
		netAndHttpInit();
	}
}

void GameHttp::netAndHttpInit(){
	debugNetPrintf(DEBUG,"Loading Sys NET MODULE\n");
	sceSysmoduleLoadModule(SCE_SYSMODULE_NET);
	SceNetInitParam netInitParam;
	int size = 2*1024*1024;
	netInitParam.memory = malloc(size);
	netInitParam.size = size;
	netInitParam.flags = 0;
	
	sceNetInit(&netInitParam);
	debugNetPrintf(DEBUG,"sceNetInit()\n");
	sceNetCtlInit();
	
	debugNetPrintf(DEBUG,"Loading Sys HTTP MODULE\n");
	sceSysmoduleLoadModule(SCE_SYSMODULE_HTTP);
	sceHttpInit(2*1024*1024);
	debugNetPrintf(DEBUG,"sceHttpInit()\n");
	
	initializedHttp = true;
}

void GameHttp::netAndHttpTerm(){
	
	initializedHttp = false;
	
	sceHttpTerm();
	sceSysmoduleUnloadModule(SCE_SYSMODULE_HTTP);
	debugNetPrintf(DEBUG,"Unloaded HTTP module\n");
	
	sceNetCtlTerm();
	sceNetTerm();
	sceSysmoduleUnloadModule(SCE_SYSMODULE_NET);
	debugNetPrintf(DEBUG,"Unloaded NET module");
	
	
}

// Server list string (JSON)
std::string GameHttp::getServerlistJSON(){
	
	std::string serversText;
	
	const char url[] = "http://jaynapps.com/csvita/getservers.php";
	
	debugNetPrintf(INFO,"GetServerlistJSON : Fullurl : \"%s\" \n" , url);
	
	
	
	int tpl = sceHttpCreateTemplate("PS Vita - CSVITA", 1, 1);
	
	
	
	debugNetPrintf(DEBUG,"GetServerlistJSON : tpl = %d \n" , tpl);
	
	int conn = sceHttpCreateConnectionWithURL(tpl, url, 0);
	
	
	debugNetPrintf(DEBUG,"GetServerlistJSON : conn = %d \n" , conn);
	
	
	int request = sceHttpCreateRequestWithURL(conn, SCE_HTTP_METHOD_GET, url, 0);
	
	
	debugNetPrintf(DEBUG,"GetServerlistJSON : request = %d \n" , request);
	
	
	int handle = sceHttpSendRequest(request, NULL, 0);
	
	
	debugNetPrintf(DEBUG,"GetServerlistJSON : handle = %d \n" , handle);
	
	if(handle < 0){
		
	}
	
	char data[32*1024];
	int read = 0;
	
	read = sceHttpReadData(request, &data, sizeof(data));
	
	
	debugNetPrintf(DEBUG,"GetServerlistJSON : read (bytes read from sceHttpReadData) = %d \n" , read);
	debugNetPrintf(INFO,"GetServerlistJSON : data = %s \n" , data);
	
	lastResponse = std::string( data , read );
	serversText = std::string( data , read );
	
	return serversText;
}

int GameHttp::registerUser(std::string username , std::string password){
	
	
	
	debugNetPrintf(INFO,"Register User : username = \"%s\"   password = \"%s\" \n" , username.c_str() , password.c_str());
	
	const char registerUrl[] = "http://jaynapps.com/csvita/registeruser.php?username=%s&password=%s";
	
	char url[512];
	snprintf(url , 512, registerUrl , username.c_str() , password.c_str() );
	
	
	
	
	debugNetPrintf(INFO,"Register User : Fullurl : \"%s\" \n" , url);
	
	
	
	int tpl = sceHttpCreateTemplate("PS Vita - CSVITA", 1, 1);
	
	
	
	debugNetPrintf(DEBUG,"Register User : tpl = %d \n" , tpl);
	
	int conn = sceHttpCreateConnectionWithURL(tpl, url, 0);
	
	
	debugNetPrintf(DEBUG,"Register User : conn = %d \n" , conn);
	
	
	int request = sceHttpCreateRequestWithURL(conn, SCE_HTTP_METHOD_GET, url, 0);
	
	
	debugNetPrintf(DEBUG,"Register User : request = %d \n" , request);
	
	
	int handle = sceHttpSendRequest(request, NULL, 0);
	
	
	debugNetPrintf(DEBUG,"Register User : handle = %d \n" , handle);
	
	if(handle < 0){
		
	}
	
	char data[1*1024];
	int read = 0;
	
	read = sceHttpReadData(request, &data, sizeof(data));
	
	
	debugNetPrintf(DEBUG,"Register User : read (bytes read from sceHttpReadData) = %d \n" , read);
	debugNetPrintf(INFO,"Register User : data = %s \n" , data);
	
	
	lastResponse = std::string( data , read );
	
	int registered = 0;
	if(read > 0){
		if(lastResponse[0] == 'R'){
			registered = 1;
			debugNetPrintf(INFO,"Register User : REGISTERED \n");
		}else{
			registered = 0;
			debugNetPrintf(INFO,"Register User : Failed to register \n");
		}
	}
	
	return registered;
}

int GameHttp::loginUser(std::string username , std::string password){
	
	
	
	debugNetPrintf(INFO,"Login User : username = \"%s\"   password = \"%s\" \n" , username.c_str() , password.c_str());
	
	const char loginUrl[] = "http://jaynapps.com/csvita/loginuser.php?username=%s&password=%s";
	
	char url[512];
	snprintf(url , 512, loginUrl , username.c_str() , password.c_str() );
	
	debugNetPrintf(INFO,"Login User : Fullurl : \"%s\" \n" , url);
	
	
	
	int tpl = sceHttpCreateTemplate("PS Vita - CSVITA", 1, 1);
	
	
	
	debugNetPrintf(DEBUG,"Login User : tpl = %d \n" , tpl);
	
	int conn = sceHttpCreateConnectionWithURL(tpl, url, 0);
	
	
	debugNetPrintf(DEBUG,"Login User : conn = %d \n" , conn);
	
	
	int request = sceHttpCreateRequestWithURL(conn, SCE_HTTP_METHOD_GET, url, 0);
	
	
	debugNetPrintf(DEBUG,"Login User : request = %d \n" , request);
	
	
	int handle = sceHttpSendRequest(request, NULL, 0);
	
	
	debugNetPrintf(DEBUG,"Login User : handle = %d \n" , handle);
	
	if(handle < 0){
		
	}
	
	char data[1*1024];
	int read = 0;
	
	
	debugNetPrintf(DEBUG,"Login User : read (bytes read from sceHttpReadData) = %d \n" , read);
	debugNetPrintf(INFO,"Login User : data = %s \n" , data);
	
	
	read = sceHttpReadData(request, &data, sizeof(data));
	
	lastResponse = std::string( data , read );
	
	int loggedin = 0;
	if(read > 0){
		if(lastResponse[0] == 'L'){
			loggedin = 1;
			debugNetPrintf(INFO,"Login User : Logged In \n");
		}else{
			loggedin = 0;
			debugNetPrintf(INFO,"Login User : Failed Login \n");
		}
	}
	
	return loggedin;
}



