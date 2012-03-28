#include "dartboard.h"

int Dartboard::HitTarget(int target, int bullSuccessRate)
{
	if (target==DartsCore::BullValue)
		return DartsCore::hitBull(bullSuccessRate);
	
	return DartsCore::attemptHit(target);
}

Dartboard::~Dartboard()
{
}

Dartboard::Dartboard()
{

}
