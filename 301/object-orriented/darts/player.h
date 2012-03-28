#ifndef PLAYER_H
#define PLAYER_H

#include "dartsCore.h"
#include <string>

using std::string;

enum PlayerID { JOE, SID } ;								//	Possible player ids are Joe and Sid

class Player
{
private:
	enum GameStage { FOCUS, FIX, WIN, WON } currentState;	

	PlayerID id;											//	player id - can be either Joe or Sid

	int score;												//	this variable holds the score
	int dartsUsed;											//	this variable is used to remember how many darts have been used up to a point

	int bullHitPercent;										//	this variable is used to store what's the chance of hitting a bull

	void setCurrentState();									//	this is used to set the current state
	void setBullHitPercent();								//	this is used to determine the chance of hitting a bull
public:
	Player(PlayerID=PlayerID::JOE);							//	default constructor; default player is Joe
	Player(const Player&);									//	copy constructor

	Player& operator=(const Player&);						//	Operator= - used for the swap

	int ThrowDart();										//	this determines how many points to aim for and returns that value

	void ScorePoints(int);									//	this handles awarding points

	const PlayerID GetID() const;							//	getter for the id
	const string GetName() const;							//	getter for name, based on id
	const int GetBullHitPercent() const;					//	getter for how well does the player hit a bull
	const int GetDartsUsed() const { return dartsUsed; }	//	getter for how many darts have been used so far

	bool HasWon()const { return currentState == GameStage::WON; }//	answers if the player has won
};


#endif