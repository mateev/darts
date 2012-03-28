#include <iostream>
#include <ctime>
#include "dartboard.h"
#include "player.h"

using namespace std;

int main()
{
	srand(time(0));
	Dartboard board;

	Player first(PlayerID::JOE);
	Player second(PlayerID::SID);

	cout << first.GetName() << endl << second.GetName() << endl;

	swap(first,second);

	cout << first.GetName() << endl << second.GetName() << endl;


	return 0;
}

