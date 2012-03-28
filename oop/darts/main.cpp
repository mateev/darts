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

	int* records = new int[Game::MAX_GAMES_COUNT+1];

	for(int i = 0;i<=Game::MAX_GAMES_COUNT;i++)
		records[i] = 0;

	for(int i = 0;i<gamesCount;i++)
		records[practiceSession.Practice()]++;

	for(int i = 0;i<=Game::MAX_GAMES_COUNT;i++)
		if(records[i]!=0)
			cout << i << ' ' << records[i] << endl;
	/*
	for(int i =0;i<gamesCount;i++)
	{
		if(practiceSession.Practice()<=6)
			cout << "J" << i;
		cout << i;
	}
	*/
	cin.get();

}
