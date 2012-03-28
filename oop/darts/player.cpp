#include "player.h"

Player& Player::operator=(const Player& other)
{
	if(this != &other)
	{
		id = other.id;
		score = other.score;
		dartsUsed = other.dartsUsed;
		setCurrentStage();
	}

	return *this;
}

Player::Player(const Player& other)
{
	id = other.id;
	score = other.score;
	dartsUsed = other.dartsUsed;
	setCurrentStage();
}

Player::Player(PlayerID inputID)
{
	id = inputID;
	score = 301;
	dartsUsed = 0;
	setCurrentStage();
}

const int Player::BullHitPercentage() const
{
	return (id == PlayerID::JOE) ? 70 : 72;
}

void Player::ScorePoint(int points)
{
	score-=points;
	setCurrentStage();
}

void Player::setCurrentStage()
{
	if(score>=100)
	{
		currentStage = GameStage::FOCUS;
	}
	else
	{
		if(score>50)
			currentStage = GameStage::FIX;
		else if(score==50)
			currentStage = GameStage::WIN;
		else
			currentStage = GameStage::WON;
	}
}

int Player::throwDart()
{
	dartsUsed++;

	int returnValue = -1;
	
	switch(currentStage)
	{
	case GameStage::FOCUS:
	case GameStage::WIN:
		return DartsCore::BullValue;
	case GameStage::FIX:
		return (score-50 <= 20) ? (score-50) : 20,BullHitPercentage();
	case GameStage::WON:
	default:
		return -1;
	}
}

string Player::GetName() const
{
	switch(id)
	{
	case JOE:
		return "Joe";
	case SID:
		return "Sid";
	default:
		return "Unknown";
	}
}