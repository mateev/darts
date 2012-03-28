#include <iostream>
#include <ctime>
#include "game.h"

using namespace std;


int main()
{
	Game activeGame = Game();

	int joeC=0;
	for(int i =0;i<1000;i++)
		joeC += (activeGame.OneVsOne(SID) == JOE) ? 1 : 0;

	cout << joeC;


	return 0;


	srand(time(0));
	Dartboard board;

	Player first(PlayerID::JOE);
	Player second(PlayerID::SID);

	cout << first.GetName() << endl << second.GetName() << endl;

	swap(first,second);

	cout << first.GetName() << endl << second.GetName() << endl;


	return 0;
}

