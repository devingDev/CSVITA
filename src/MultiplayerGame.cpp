#include "MultiplayerGame.hpp"
#include "../Box2D/Box2D.h"

#include <debugnet.h>
#include <vita2d.h>
#include <string>



//
//b2Vec2 b2_grav(0.0f , 0.0f);
//b2World b2_world(b2_grav);


void MultiplayerGame::Draw(){
	debugNetPrintf(DEBUG,"MultiplayerGame Draw Start \n");
	debugNetPrintf(DEBUG,"MultiplayerGame Draw : vita2d_start_drawing() \n");
	vita2d_start_drawing();
	debugNetPrintf(DEBUG,"MultiplayerGame Draw : vita2d_clear_screen \n");
	vita2d_clear_screen();
	
	/* NOW DO DRAWINGS : */
	
	
	
	debugNetPrintf(DEBUG,"MultiplayerGame Draw : for loop (All players) start \n");
	for(int i = 0 ; i < MAX_PLAYERS_ ; i++){
		
		//if(players[i].isInServer){
		//	//if player is on server do ... (draw / calc etc..)
		//
		//}
		
		
		
		//vita2d_draw_texture(imagePlayer, players[i].getX() , players[i].getY() );
		
		vita2d_draw_rectangle(players[i].getX() , players[i].getY(), 16, 18, RGBA8(0x99, 0x40, 0xF3, 0xFF));
		
		
	}
	debugNetPrintf(DEBUG,"MultiplayerGame Draw : for loop end \n");
	
	if(imagePlayer != NULL){
		debugNetPrintf(DEBUG,"MultiplayerGame Draw : vita2d_draw_texture \n");
		vita2d_draw_texture(imagePlayer, 64 , 64);
	}
	
	debugNetPrintf(DEBUG,"MultiplayerGame Draw : vita2d_draw_rectangle \n");
	vita2d_draw_rectangle(32, 32, 32, 48, RGBA8(0x99, 0xFF, 0xF3, 0xFF));
	
	/* END OF DRAWINGS! */
	
	debugNetPrintf(DEBUG,"MultiplayerGame Draw : vita2d_end_drawing() \n");
	vita2d_end_drawing();
	debugNetPrintf(DEBUG,"MultiplayerGame Draw : vita2d_swap_buffers() \n");
	vita2d_swap_buffers();
	debugNetPrintf(DEBUG,"MultiplayerGame Draw End \n");
}

void MultiplayerGame::HandleInput(){
	debugNetPrintf(DEBUG,"MultiplayerGame HandleInput Start \n");
	debugNetPrintf(DEBUG,"MultiplayerGame HandleInput : vitpad left analog x : %d \n" , vitaPad.left_analog_x );
	debugNetPrintf(DEBUG,"MultiplayerGame HandleInput : vitpad left analog y : %d \n" , vitaPad.left_analog_y );
	debugNetPrintf(DEBUG,"MultiplayerGame HandleInput : vitpad right analog x : %d \n" , vitaPad.right_analog_x );
	debugNetPrintf(DEBUG,"MultiplayerGame HandleInput : vitpad right analog y : %d \n" , vitaPad.right_analog_y );
	players[0].controllerMove(vitaPad.left_analog_x , vitaPad.left_analog_y);
	debugNetPrintf(DEBUG,"MultiplayerGame HandleInput End \n");
	
}

void MultiplayerGame::Loop(){
	debugNetPrintf(DEBUG,"MultiplayerGame Loop Start \n");
	HandleInput();
	Draw();
	debugNetPrintf(DEBUG,"MultiplayerGame Loop End \n");
	
}


void MultiplayerGame::passVitaPad(VitaPad &vitaPadS){
	vitaPad = vitaPadS;
}
		
		


MultiplayerGame::MultiplayerGame(){
	debugNetPrintf(DEBUG,"start of mpgame constructor\n");
	
	
	
	debugNetPrintf(DEBUG,"loading imagePlayer with vita2d_load_PNG_file(path)\n");
	imagePlayer = vita2d_load_PNG_file(imagePlayerPath.c_str());
	
	if(imagePlayer != NULL){
		debugNetPrintf(DEBUG,"imagePlayer was loaded!\n");
	}else{
		debugNetPrintf(DEBUG,"imagePlayer == NULL  , was not loaded!\n");
	}
	
	
	//
	players.resize(MAX_PLAYERS_);
	
	debugNetPrintf(DEBUG,"assigning 1/60 to timeStep\n");
	timeStep = 1.0f / 60.0f;
	
	//b2World b2_worldT(b2_grav);
	//b2_world = b2_worldT;
	//timeStep = 1.0f / 60.0f;
	//
	//
	groundBodyDef.position.Set(0.0f, -10.0f);
	groundBody = b2_world.CreateBody(&groundBodyDef);
	
	groundBox.SetAsBox(50.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);
	
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 4.0f);
	b2Body* body = b2_world.CreateBody(&bodyDef);
    
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	
	body->CreateFixture(&fixtureDef);
	
	
	for(int i = 0; i < MAX_PLAYERS_ ; i++){
		
		players[i].bodyDef.type = b2_dynamicBody;
		players[i].bodyDef.position.Set(0.0f, 4.0f);
		players[i].dynamicBox.SetAsBox(1.0f, 1.0f);
		players[i].fixtureDef.shape = &players[i].dynamicBox;
		players[i].fixtureDef.density = 1.0f;
		players[i].fixtureDef.friction = 0.3f;
		players[i].body = b2_world.CreateBody(&players[i].bodyDef);
		players[i].body->CreateFixture(&players[i].fixtureDef);
		
	}


	debugNetPrintf(DEBUG,"Mpgame : for loop test box2d gravity = 0.0f \n");
	for (int i = 0; i < 60; ++i)
		{
		 b2_world.Step(timeStep, velocityIterations, positionIterations);
		 b2Vec2 position = body->GetPosition();
		 float angle = body->GetAngle();
		 debugNetPrintf(INFO,"%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
		}

	
	debugNetPrintf(DEBUG,"End of Mpgame constructor\n");
}