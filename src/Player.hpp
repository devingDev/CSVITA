#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player
{
	public:
	  std::string getPosString();
	  void controllerMove(int ax , int ay);
	  void controllerRotate(bool turn_right); // false means turning left , else turning right ;)
	  int getX();
	  int getY();
	  void SetPositionNetwork(float xNP , float yNP);
	  bool inServer;
	  float getFloatX();
	  float getFloatY();
	  float getRad();
	  bool takeDamage(int dmg);
	  void calibrateAnalog(int ax , int ay);
	  Player();
	  Player(unsigned char cal_x , unsigned char cal_y);
	  Player(int x , int y , int hp);
	  
	private:
	  int x;
	  int y;
	  float xF;
	  float yF;
	  float rad;
	  float turn_amount;
	  int hp;
	  double movementSpeed;
	  unsigned char calibration_x;
	  unsigned char calibration_y;
	
};

#endif