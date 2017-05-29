#define VITASDK



#include "CSVitaGame.hpp"
#include <debugnet.h>
#include <psp2/kernel/threadmgr.h> 
#include <psp2/kernel/processmgr.h>

#define ip_server "192.168.1.85"
#define port_server 18194


extern "C"
{
    unsigned int sleep(unsigned int seconds)
    {
        sceKernelDelayThread(seconds*1000*1000);
        return 0;
    }

    int usleep(useconds_t usec)
    {
        sceKernelDelayThread(usec);
        return 0;
    }

    void __sinit(struct _reent *);
}

__attribute__((constructor(101)))
void pthread_setup(void) 
{
    pthread_init();
    __sinit(_REENT);
}
int main(){
	
	int ret;
	ret=debugNetInit(ip_server,port_server,DEBUG);
	debugNetPrintf(DEBUG,"Test debug level %d\n",ret);
	
	CSVitaGame csvitagame;
	csvitagame.Start();
	
	debugNetFinish();
	sceKernelExitProcess(0);
	return 0;
}