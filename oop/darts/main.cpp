#include <iostream>
#include <ctime>
#include "game.h"

using namespace std;

void printPracticeStatistics(long=10000);
void printGameplayStatistics(long=10000);
double gamePlayStatistics(GameType = JOE_FIRST,long=10000);

int main()
{
	srand(time(0));

	int sampleSize;

	cout << "Sample size: ";
	cin >> sampleSize;

	printPracticeStatistics(sampleSize);

	printGameplayStatistics(sampleSize);

	return 0;
}

double gamePlayStatistics(GameType type,long gamesCount)
{
	PlayerID firstPlayer;
	PlayerID lastWinner;

	if(type == SWITCH)
		firstPlayer = (DartsCore::randomSign() < 0) ? JOE : SID;
	else
		firstPlayer = (type==JOE_FIRST) ? JOE : SID;

	lastWinner = firstPlayer == JOE ? SID : JOE;

	int gamesWon = 0;
	Game gameSession = Game();

	for(long i = 0;i<gamesCount; i++)
	{
		if(type == SWITCH && lastWinner==firstPlayer)
			firstPlayer = (lastWinner==SID) ? JOE : SID;

		lastWinner = gameSession.OneVsOne(firstPlayer);

		gamesWon += (lastWinner == JOE) ? 1 : 0;
	}

	return ((double)gamesWon/gamesCount)*100;
}

void printGameplayStatistics(long gamesCount)
{
	cout << "\tEstimates of Joe's Percentage Success Rate" << endl;

	cout << "Rule\t";

	for(int i = 1; i<=5;i++)
		cout << "Run " << i << '\t';

	cout << "Mean" << endl;

	double meanStat;
	double currentStat;

	for(int gameType = 1;gameType<=3;gameType++)
	{
		cout << gameType << '\t';

		meanStat = 0;

		for(int run = 1; run <= 5; run++)
		{
			currentStat = gamePlayStatistics((GameType)gameType,gamesCount);
			cout << currentStat << '\t';
			meanStat+=currentStat;
		}

		cout << meanStat/5 << endl;
	}

	cout << endl << "Rules:" << endl
			<< "\t1. Joe throws first" << endl
			<< "\t2. Sid throws first" << endl
			<< "\t3. Toss a coin to start, loser starts next" << endl;
}

void printPracticeStatistics(long gamesCount)
{
	int totalDartsCount = 0;
	int totalGamesCount = 0;
	double totalPercent = 0;

	Game practiceSession = Game();

	long* records = new long[Game::MAX_GAMES_COUNT+1];

	for(int i = 0;i<=Game::MAX_GAMES_COUNT;i++)
		records[i] = 0;

	for(int i = 0;i<gamesCount;i++)
		records[practiceSession.Practice()]++;

	cout << "#Statistics for Joe playing by himself" << endl;
	cout << "Darts:\tGames:\tPercent:" << endl;

	for(int i = 0;i<=Game::MAX_GAMES_COUNT;i++)
	{
		if(records[i]!=0)
		{
			totalDartsCount += i;
			totalGamesCount += records[i];
			totalPercent	+= ((double)records[i]/gamesCount)*100;
			cout << i << '\t' << records[i] << '\t' << ((double)records[i]/gamesCount)*100 << '%' << endl;
		}
	}

	for(int i =0;i<25;i++)	cout << '=';

	cout << endl
			<< totalDartsCount << '\t' << totalGamesCount << '\t' << totalPercent << '%' << endl;

	delete [] records;
}
