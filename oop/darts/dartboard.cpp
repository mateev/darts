#include "dartboard.h"

//	This handles hitting a target on the board
int Dartboard::HitTarget(int target, int bullSuccessRate)
{
	if (target==DartsCore::BULLVALUE)				//	If the target is the bull ...
		return DartsCore::hitBull(bullSuccessRate);		//	... attempt to hit, based on the success rate and return the result
	
	return DartsCore::attemptHit(target);			//	Return the result of hitting a target
}
