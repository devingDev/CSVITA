#define VITASDK



#include "CSVitaGame.hpp"
#include <psp2/kernel/threadmgr.h> 




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
	CSVitaGame csvitagame;
	csvitagame.Start();
	
	return 0;
}