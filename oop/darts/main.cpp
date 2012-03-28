#include <iostream>
#include <ctime>
#include "game.h"

using namespace std;

void printPracticeStatistics(long=10000);

int main()
{
	printPracticeStatistics(100);

	return 0;
}

void printPracticeStatistics(long gamesCount)
{
	Game practiceSession = Game();

	for(int i =0;i<gamesCount;i++)
	{
		if(practiceSession.Practice()<=6)
			cout << "J" << i;
		cout << i;
	}

	cin.get();

}
