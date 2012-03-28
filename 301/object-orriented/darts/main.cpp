#include <iostream>
#include <ctime>
#include "game.h"

using namespace std;

void printPracticeStatistics(long=10000);						//	Prints the practice statistics
void printGameplayStatistics(long=10000);						//	Prints game statistics
double gamePlayStatistics(GameType = JOE_FIRST,long=10000);		//	Calculates the percentage of games won by joe, following a rule

int main()
{
	srand(time(0));

	int sampleSize;

	cout << "Input sample size: ";
	cin >> sampleSize;

	while(sampleSize<=0)
	{
		cout << "Sample size must be bigger than zero!" << endl << "Input sample size: ";
		cin >> sampleSize;
	}

	printPracticeStatistics(sampleSize);

	printGameplayStatistics(sampleSize);

	return 0;
}

//	Calculates the percentage of games won by joe, following a rule
double gamePlayStatistics(GameType type,long gamesCount)
{
	PlayerID firstPlayer;
	PlayerID lastWinner;

	Game gameSession = Game();

	int joeGamesWon = 0;											//	This count how many games has Joe won

	if(type == SWITCH)												//	If it's a game of switch ...
		firstPlayer = (DartsCore::randomSign() < 0) ? JOE : SID;		//	... throw a coin to determine who goes first
	else															//	Otherwise it must be a non-switch game...
		firstPlayer = (type==JOE_FIRST) ? JOE : SID;					//	... so select who goes first, based on the game type

	lastWinner = (firstPlayer == JOE) ? SID : JOE;					//	Assume the winner from the last game is not who goes first;
																	//	This is to make sure that whoever goes first won't be swapped before throwing

	for(long i = 0;i<gamesCount; i++)								//	Go over all games...
	{
		if(type == SWITCH && lastWinner==firstPlayer)					//	If it's a switch game and the winner is the one who played last ...
			firstPlayer = (lastWinner==SID) ? JOE : SID;					//	... the looser should play first, so swap the players

		lastWinner = gameSession.OneVsOne(firstPlayer);					//	Play a 301 game and record who won

		joeGamesWon += (lastWinner == JOE) ? 1 : 0;						//	If Joe won, add a point to his win counter
	}

	return ((double)joeGamesWon/gamesCount)*100;					//	Return how much from all the games did Joe win
}

void printGameplayStatistics(long gamesCount)
{
	double meanStat;		//	This will hold the overall mean value for the game type
	double currentStat;		//	This will hold the mean value for one run

	cout << "\tEstimates of Joe's Percentage Success Rate" << endl;

	cout << "Rule\t";

	for(int i = 1; i<=5;i++)
		cout << "Run " << i << '\t';

	cout << "Mean" << endl;

	for(int gameType = 1;gameType<=3;gameType++)
	{
		meanStat = 0;

		cout << gameType << '\t';

		for(int run = 1; run <= 5; run++)
		{
			currentStat = gamePlayStatistics((GameType)gameType,gamesCount);
			meanStat+=currentStat;

			cout << currentStat << '\t';
		}

		cout << meanStat/5 << endl;
	}

	cout << endl << "Rules:" << endl
			<< "\t1. Joe throws first" << endl
			<< "\t2. Sid throws first" << endl
			<< "\t3. Toss a coin to start, loser starts next" << endl;
}

//	Prints the practice statistics
void printPracticeStatistics(long gamesCount)
{
	int totalDartsCount = 0;			//	This will hold how many darts have been thrown over the whole run
	int totalGamesCount = 0;			//	This will hold how many games have been played over the whole run
	double totalPercent = 0;			//	This wiil hold the total percentage; mainly for show - displays 100%

	Game practiceSession = Game();							//	Initialize the game session

	long* records = new long[Game::MAX_GAMES_COUNT+1];		//	Initialize the array of statistical records

	for(int i = 0;i<=Game::MAX_GAMES_COUNT;i++)				//	Populate the array with zeroes
		records[i] = 0;

	for(int i = 0;i<gamesCount;i++)							//	Play gamesCount-games
		records[practiceSession.Practice()]++;					//	... and increase counter for the corresponding game type

	cout << "#Statistics for Joe playing by himself" << endl;
	cout << "Darts:\tGames:\tPercent:" << endl;

	for(int i = 0;i<=Game::MAX_GAMES_COUNT;i++)																//	Go over all records
	{
		if(records[i]!=0)																						//	If the i-th record exists
		{
			totalDartsCount += i;																					//	... increase the total darts count
			totalGamesCount += records[i];																			//	... increase the total games count
			totalPercent	+= ((double)records[i]/gamesCount)*100;													//	... increase the total percent count
			cout << i << '\t' << records[i] << '\t' << ((double)records[i]/gamesCount)*100 << '%' << endl;			//	... display statistics ...
		}
	}

	for(int i =0;i<25;i++)	cout << '=';																	//	Make a line of 25 equal signs

	cout << endl
			<< totalDartsCount << '\t' << totalGamesCount << '\t' << totalPercent << '%' << endl;			//	Display total

	delete [] records;																						//	Cleanup!
}
