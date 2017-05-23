#include <psp2/sysmodule.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/net/net.h>
#include <psp2/net/netctl.h>
#include <psp2/net/http.h>

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
	sceSysmoduleLoadModule(SCE_SYSMODULE_NET);
	SceNetInitParam netInitParam;
	int size = 2*1024*1024;
	netInitParam.memory = malloc(size);
	netInitParam.size = size;
	netInitParam.flags = 0;
	sceNetInit(&netInitParam);
	sceNetCtlInit();
	
	sceSysmoduleLoadModule(SCE_SYSMODULE_HTTP);
	sceHttpInit(2*1024*1024);
	
	initializedHttp = true;
}

void GameHttp::netAndHttpTerm(){
	
	initializedHttp = false;
	
	sceHttpTerm();
	sceSysmoduleUnloadModule(SCE_SYSMODULE_HTTP);
	
	sceNetCtlTerm();
	sceNetTerm();
	sceSysmoduleUnloadModule(SCE_SYSMODULE_NET);
	
	
}

// Server list string (JSON)
std::string GameHttp::getServerlistJSON(){
	
	std::string serversText;
	
	const char serverlistjsonurl[] = "http://jaynapps.com/csvita/getservers.php";
	
	int tpl = sceHttpCreateTemplate("PS Vita - CSVITA", 1, 1);
	int conn = sceHttpCreateConnectionWithURL(tpl, serverlistjsonurl, 0);
	int request = sceHttpCreateRequestWithURL(conn, SCE_HTTP_METHOD_GET, serverlistjsonurl, 0);
	int handle = sceHttpSendRequest(request, NULL, 0);
	
	if(handle < 0){
		
	}
	
	char data[32*1024];
	int read = 0;
	
	read = sceHttpReadData(request, &data, sizeof(data));
	
	lastResponse = std::string( data , read );
	serversText = std::string( data , read );
	
	return serversText;
}

int GameHttp::registerUser(std::string username , std::string password){
	
	const char registerUrl[] = "http://jaynapps.com/csvita/registeruser.php?username=%s&password=%s";
	
	char url[512];
	snprintf(url , 512, registerUrl , username.c_str() , password.c_str() );
	
	int tpl = sceHttpCreateTemplate("PS Vita - CSVITA", 1, 1);
	int conn = sceHttpCreateConnectionWithURL(tpl, url, 0);
	int request = sceHttpCreateRequestWithURL(conn, SCE_HTTP_METHOD_GET, url, 0);
	int handle = sceHttpSendRequest(request, NULL, 0);
	
	if(handle < 0){
		
	}
	
	char data[1*1024];
	int read = 0;
	
	read = sceHttpReadData(request, &data, sizeof(data));
	
	lastResponse = std::string( data , read );
	
	int registered = 0;
	if(read > 0){
		if(lastResponse[0] == 'R'){
			registered = 1;
		}
	}
	
	return registered;
}

int GameHttp::loginUser(std::string username , std::string password){
	
	const char loginUrl[] = "http://jaynapps.com/csvita/loginuser.php?username=%s&password=%s";
	
	char url[512];
	snprintf(url , 512, loginUrl , username.c_str() , password.c_str() );
	
	int tpl = sceHttpCreateTemplate("PS Vita - CSVITA", 1, 1);
	int conn = sceHttpCreateConnectionWithURL(tpl, url, 0);
	int request = sceHttpCreateRequestWithURL(conn, SCE_HTTP_METHOD_GET, url, 0);
	int handle = sceHttpSendRequest(request, NULL, 0);
	
	if(handle < 0){
		
	}
	
	char data[1*1024];
	int read = 0;
	
	read = sceHttpReadData(request, &data, sizeof(data));
	
	lastResponse = std::string( data , read );
	
	int registered = 0;
	if(read > 0){
		if(lastResponse[0] == 'L'){
			registered = 1;
		}
	}
	
	return registered;
}



