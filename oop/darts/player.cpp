#include "player.h"

//	Operator= - used for the swap
Player& Player::operator=(const Player& other)
{
	if(this == &other)				// if both sides are the same object...
	{
		return *this;					// ... just return it
	}

	id = other.id;				
	score = other.score;		
	dartsUsed = other.dartsUsed;
	setCurrentState();				//	Reinitialize state
	setBullHitPercent();			//	Recalculate hit percent

	return *this;
}

//	Copy constructor
Player::Player(const Player& other)
{
	id = other.id;
	score = other.score;
	dartsUsed = other.dartsUsed;
	setCurrentState();				//	Initialize state
	setBullHitPercent();			//	Calculate hit percent
}

//	Default constructor
Player::Player(PlayerID inputID)
{
	id = inputID;
	score = 301;
	dartsUsed = 0;
	setCurrentState();				//	Initialize state
	setBullHitPercent();			//	Calculate hit percent
}

//	Getter for how well does the player hit a bull
const int Player::GetBullHitPercent() const
{
	return bullHitPercent;
}

//	This handles awarding points to the player
void Player::ScorePoints(int points)
{
	switch(currentState)
	{
	case GameStage::WON:													// If the player has won...
		return;																	// ... no use updating
	case GameStage::WIN:													// If the player is aiming to win ...
		score -= (points==DartsCore::BULLVALUE) ? DartsCore::BULLVALUE : 0;		//	... award points only if he has hit a bull
		break;
	case GameStage::FIX:
		if(score-points>=50)
			score -= points;
		break;
	default:
		score -= points;														// Award points as usual
	}

	setCurrentState();														//	There couls be a need for a change of state, so reinitialize it
}

//	This is used to set the current state
void Player::setCurrentState()
{
	if(score>=100)							// If the score is above 100
	{
		currentState = GameStage::FOCUS;		// ... the player should try to have his points to around 100
	}
	else									// Otherwise
	{
		if(score>50)							// ... If the score is above 50
			currentState = GameStage::FIX;			// ... player should be trying to fix in on 50
		else if(score==50)						//	...If the score is 50
			currentState = GameStage::WIN;			// ... player should be trying to win (score a bull)
		else
			currentState = GameStage::WON;		//	Otherwise score is zero, so the player has won
	}
}

//	This determines how many points to aim for and returns that value
int Player::ThrowDart()
{
	dartsUsed++;									// Note darts usage
		
	switch(currentState)
	{
	case GameStage::FOCUS:							//	If player is trying to focus (or)
	case GameStage::WIN:							//  If player is triyng to win
		return DartsCore::BULLVALUE;					//	... best chance is to aim for a bull
	case GameStage::FIX:							//	If the player is trying to fix on 50
		return (score-50 <= 20) ? (score-50) : 20;		//	...	If the score can be brought down to 50 in 1 shot, will attempt to take it, otherwise will do the closest possible
	default:
		return -1;									//	Otherwise must have won
	}
}

//	Getter for name, based on id
const string Player::GetName() const
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

//	this is used to determine the chance of hitting a bull
void Player::setBullHitPercent() 
{ 
	bullHitPercent = (id == PlayerID::JOE) ? 70 : 72;	//	For Joe it's 70, otherwise it must be Sid, so 72
}

//	getter for the id
const PlayerID Player::GetID() const
{
	return id;
}