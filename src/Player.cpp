
#include <string>


#include "Player.hpp"

const float DEFAUL_TURN_AMOUNT = 0.0125f;
const unsigned char DEFAULT_CAL = 127;
const int DEFAULT_X_POS = 50;
const int DEFAULT_Y_POS = 50;
const int DEFAULT_HP = 100;
unsigned char ANALOG_X_THRESHOLD_MIN = 126;
unsigned char ANALOG_X_THRESHOLD_MAX = 128;
unsigned char ANALOG_Y_THRESHOLD_MIN = 126;
unsigned char ANALOG_Y_THRESHOLD_MAX = 128;
unsigned char ANALOG_THRESHOLD = 3;


std::string Player::getPosString(){
	return std::to_string(xF) + ":" + std::to_string(yF);
}

void Player::SetPositionNetwork(float xNP , float yNP){
	inServer = true;
	xF = xNP;
	yF = yNP;
	x = static_cast<int>(xF);
	y = static_cast<int>(yF);
}

Player::Player(){
	x = DEFAULT_X_POS;
	y = DEFAULT_Y_POS;
	xF = x;
	yF = y;
	hp = DEFAULT_HP;
	movementSpeed = 0.0125;
	calibration_x   = DEFAULT_CAL;
	calibration_y   = DEFAULT_CAL;
	rad = 0.0f;
	turn_amount = DEFAUL_TURN_AMOUNT;
}

Player::Player(unsigned char cal_x , unsigned char cal_y){
	x = DEFAULT_X_POS;
	y = DEFAULT_Y_POS;
	xF = x;
	yF = y;
	hp = DEFAULT_HP;
	inServer = false;
	movementSpeed = 0.0125;
	calibration_x   = cal_x;
	calibration_y   = cal_y;
	ANALOG_X_THRESHOLD_MIN = cal_x - ANALOG_THRESHOLD;
	ANALOG_X_THRESHOLD_MAX = cal_x + ANALOG_THRESHOLD;
	ANALOG_Y_THRESHOLD_MIN = cal_y - ANALOG_THRESHOLD;
	ANALOG_Y_THRESHOLD_MAX = cal_y + ANALOG_THRESHOLD;
	rad = 0.0f;
	turn_amount = DEFAUL_TURN_AMOUNT;
}  

Player::Player(int xS , int yS , int hpS){
	x = xS;
	y = yS;
	hp = hpS;
	calibration_x   = DEFAULT_CAL;
	calibration_y   = DEFAULT_CAL;
	rad = 0.0f;
	turn_amount = DEFAUL_TURN_AMOUNT;
}

void Player::calibrateAnalog(int ax , int ay){
	calibration_x = ax;
	calibration_y = ay;
	ANALOG_X_THRESHOLD_MIN = ax - ANALOG_THRESHOLD;
	ANALOG_X_THRESHOLD_MAX = ax + ANALOG_THRESHOLD;
	ANALOG_Y_THRESHOLD_MIN = ay - ANALOG_THRESHOLD;
	ANALOG_Y_THRESHOLD_MAX = ay + ANALOG_THRESHOLD;
}

void Player::controllerMove(int ax , int ay)
{
	// "Deadzone checks before moving"
	if(ax < ANALOG_X_THRESHOLD_MIN || ax > ANALOG_X_THRESHOLD_MAX)
	{
		xF += ( (ax - calibration_x) * movementSpeed);
		x = static_cast<int>(xF);
	}
	if(ay < ANALOG_Y_THRESHOLD_MIN || ay > ANALOG_Y_THRESHOLD_MAX)
	{
		yF += ( ( ay - calibration_y ) * movementSpeed );
		y = static_cast<int>(yF);
	}
	
	
}

void Player::controllerRotate(bool turn_right){
	rad += (turn_right) ? (turn_amount) : (-turn_amount);
}

bool Player::takeDamage(int dmg){
	hp -= dmg;
	if(hp <= 0){
		return true;
	}
	return false;
}

float Player::getFloatX(){
	return xF;
}
float Player::getFloatY(){
	return yF;
}
int Player::getX(){
	return x;
}
int Player::getY(){
	return y;
}
float Player::getRad(){
	return rad;
}
