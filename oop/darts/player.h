#ifndef PLAYER_H
#define PLAYER_H

#include "dartsCore.h"
#include <string>
#include <tuple>

using std::string;
using std::tuple;
using std::tie;

enum PlayerID { JOE, SID } ;

typedef tuple<int,int> Target;


class Player
{
private:
	PlayerID id;
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