#ifndef MULTIPLAYERGAME_HPP
#define MULTIPLAYERGAME_HPP


#include "../Box2D/Box2D.h"
#include <vector>
#include <vita2d.h>
#include "Player.hpp"
#include "VitaPad.hpp"


class MultiplayerGame{
	public:
		MultiplayerGame();
		void passVitaPad(VitaPad &vitaPad);
		void Loop();
		
		
	private:
		b2Vec2 b2_grav{0.0f , 0.0f};
		b2World b2_world{b2_grav};
		
		b2BodyDef groundBodyDef;
		b2Body* groundBody;
		b2PolygonShape groundBox;
		
		VitaPad vitaPad;
		
		std::string imagePlayerPath = "app0:images/player.png";;
		vita2d_texture *imagePlayer;
		std::vector<Player> players;
		
		float timeStep;
		int velocityIterations = 6;
		int positionIterations = 2;
		int MAX_PLAYERS_ = 32;

		void HandleInput();
		void Draw();
	
	
	
















};
#endif


