#include <iostream>
#include "dartboard.h"
#include "player.h"

using namespace std;

int main()
{
	Player joe(PlayerID::JOE);
	Dartboard board;

	cout << joe.GetName();
	
	cout << board.HitTarget(joe.throwDart(),joe.BullHitPercentage());

	return 0;
}

