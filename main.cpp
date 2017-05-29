#include <psp2/kernel/processmgr.h>
#include <psp2/ctrl.h>
#include <vita2d.h>
#include <psp2/net/net.h>
#include <psp2/net/netctl.h>

#include <unistd.h>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>


#include "player.h"

// NET STUFF START
# define INADDR_ANY ((unsigned long int) 0x00000000)
#define NET_INIT_SIZE 1*1024*1024
#define PORT 50000  //The port on which to listen for incoming data
#define NPACK 10
#define BUFLEN 8192
#define BUFSIZE 8192
#define SRV_IP "37.120.174.141"

static int myserversock = 0;
static void *net_memory = NULL;
char buf[8192];
// NET STUFF END

void ReadInputs();

Player player1;
SceCtrlData pad;
bool gameRunning;

void diep(char *s)
{
	perror(s);
	exit(1);
}

unsigned int inet_addr(char *str)
{
	int a, b, c, d;
	char arr[4];
	sscanf(str, "%d.%d.%d.%d", &a, &b, &c, &d);
	arr[0] = a; arr[1] = b; arr[2] = c; arr[3] = d;
	return *(unsigned int *)arr;
}

int main(int argc, char *argv[]) {
	sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
	
	// NET TEST START!!!!!
	struct sockaddr_in si_other;
	int s, i;
	socklen_t slen = sizeof(si_other);
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
		diep("socket err");

	memset((char *)&si_other, 0, sizeof(si_other));

	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	if (inet_aton(SRV_IP, &si_other.sin_addr) == 0) {
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}

	for (i = 0; i<NPACK; i++) {
		printf("Sending packet %d\n", i);
		sprintf(buf, "This is packet %d\n", i);
		if (sendto(s, buf, BUFLEN, 0, (sockaddr)&si_other, slen) == -1)
			diep("sendto()");
	}
	close(s);



	/*SceNetSockaddrIn server;

	if (sceNetShowNetstat() == SCE_NET_ERROR_ENOTINIT) {
		net_memory = malloc(NET_INIT_SIZE);

		SceNetInitParam initparam;
		initparam.memory = net_memory;
		initparam.size = NET_INIT_SIZE;
		initparam.flags = 0;

		sceNetInit(&initparam);
		sceKernelDelayThread(100 * 1000);
	}

	server.sin_len = sizeof(server);
	server.sin_family = SCE_NET_AF_INET;
	sceNetInetPton(SCE_NET_AF_INET, IP, &server.sin_addr);
	server.sin_port = sceNetHtons(PORT);
	memset(server.sin_zero, 0, sizeof(server.sin_zero));

	myserversock = sceNetSocket("vitanettest", SCE_NET_AF_INET, SCE_NET_SOCK_DGRAM, 0);

	
	bzero(buf, BUFSIZE);
	strcpy(buf, "LOGINbizzy:asdf12");
	sceNetSendto(myserversock, buf, BUFSIZE, 0, (SceNetSockaddr *)&server, sizeof(server));

	//sceNetConnect(myserversock, (SceNetSockaddr *)&server, sizeof(server));

	bzero(buf, BUFSIZE);
	unsigned int add_len_server = 0;
	sceNetRecvfrom(myserversock, buf , BUFSIZE , 0 , (SceNetSockaddr *)&server, &add_len_server);

	sceNetSocketClose(myserversock);
	// NET TEST END!!!!!*/


	
	gameRunning = true;
	

	
	
	vita2d_pgf *pgf;
	vita2d_pvf *pvf;
	vita2d_texture *image;
	int images_x[15];
	int images_y[15];
	//float rad = 0.0f;
	
	unsigned char left_analog_calibration_x = 127;
	unsigned char left_analog_calibration_y = 127;
	
	vita2d_init();
	vita2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));
	
	pgf = vita2d_load_default_pgf();
	pvf = vita2d_load_default_pvf();
	
	std::string imagePath("app0:images/player.png");
	image = vita2d_load_PNG_file(imagePath.c_str());
	for(int i = 0 ; i < 15 ; i++){
		images_x[i] = i * 60;
		images_y[i] = 256;
	}
	
	memset(&pad, 0, sizeof(pad));
	sceCtrlPeekBufferPositive(0, &pad, 1);
	left_analog_calibration_x = pad.lx;
	left_analog_calibration_y = pad.ly;

	player1 = Player(pad.lx , pad.ly);
	
	while(gameRunning){
		
		
		ReadInputs();
		
		
		
		
		
		vita2d_start_drawing();
		vita2d_clear_screen();
		
		vita2d_draw_rectangle(20, 20, 400, 250, RGBA8(125, 0, 0, 255));
		vita2d_draw_rectangle(680, 350, 100, 150, RGBA8(0, 0, 255, 255));
		vita2d_draw_fill_circle(200, 420, 100, RGBA8(0, 255,0 ,255));
		vita2d_draw_line(500, 30, 800, 300, RGBA8(255, 0, 255, 255));

		vita2d_pgf_draw_textf(pgf, 100, 30, RGBA8(255,255,255,255), 1.0f, "FX: %.4f   FY: %.4f   X: %d    Y: %d   LAX: %d   LAY: %d   Rad: %.4f" , player1.getFloatX() , player1.getFloatY() , player1.getX() , player1.getY() , pad.lx , pad.ly , player1.getRad() );
		vita2d_pvf_draw_text(pvf, 400, 80, RGBA8(255,255,255,255), 1.0f, "Press X to calibrate analog stick.");
		
		//vita2d_draw_texture_rotate(image, 940/2, 544/2, rad);
		
		// "PLAYER image"
		vita2d_draw_texture_rotate(image, player1.getX(), player1.getY(), player1.getRad() );
		
		
		for(int i = 0 ; i < 15 ; i++){
			vita2d_draw_texture_rotate(image, images_x[i], images_y[i], player1.getRad() );
		}

		vita2d_end_drawing();
		vita2d_swap_buffers();

		
		
		
		

		
		
	}
	
	
	
	vita2d_fini();
	vita2d_free_texture(image);
	vita2d_free_pgf(pgf);
	vita2d_free_pvf(pvf);
	
	
	sceKernelDelayThread(10*1000*1000);	
	sceKernelExitProcess(0);
    return 0;
}


void ReadInputs(){
	
	sceCtrlPeekBufferPositive(0, &pad, 1);
	
	// QUIT GAME
	if (pad.buttons & SCE_CTRL_START)
		gameRunning = false;

	if(pad.buttons & SCE_CTRL_CROSS){
		player1.calibrateAnalog(pad.lx , pad.ly);
		
	}
	
	// ROTATE
	if(pad.buttons & SCE_CTRL_L1 || pad.buttons & SCE_CTRL_LTRIGGER){
		player1.controllerRotate(false);
	}else if(pad.buttons & SCE_CTRL_R1 || pad.buttons & SCE_CTRL_RTRIGGER){
		player1.controllerRotate(true);	
	}
	
	// MOVE
	player1.controllerMove(pad.lx  , pad.ly);
	
	
}










//#include <cstdio>
//#include <sstream>
//#include <vector>
//#include "debugScreen.h"
//#define printf psvDebugScreenPrintf

//int main(int argc, char *argv[]) {
//	psvDebugScreenInit();
//	std::stringstream output;
//	std::vector<std::string> hello = { "Hello" };
//	hello.push_back(",");
//	hello.push_back(" C++ ");
//	hello.push_back("world!");
//	for (auto &s : hello) {
//		// std::cout does't work ATM :(
//		output << s;
//	}
//	output << std::endl;
//	printf("%s\n", output.str().c_str());
//	
//	vita2d_load_PNG_file(const char *filename);
//	
//	sceKernelDelayThread(10*1000*1000);	
//	sceKernelExitProcess(0);
//	return 0;
//}
