#ifndef PLAYER_H
#define PLAYER_H

#include "dartsCore.h"
#include <string>

using std::string;

class Player
{
private:
	enum PlayerID { JOE, SID } id;
	enum GameStage { FOCUS, FIX, WIN, WON } currentStage;

	int score;
	int dartsUsed;

	void setCurrentStage();
public:
	Player(PlayerID=PlayerID::JOE);		//	default constructor
	Player(const Player&);				//	copy constructor

	Player& operator=(const Player&);	//	operator= for the swap

	int throwDart();

	void ScorePoint(int);

	string GetName() const;				
	const int BullHitPercentage() const;
	bool HasWon()const { return currentStage == GameStage::WON; }
};


#endif