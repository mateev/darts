#include <iostream>
#include <ctime>
#include "gameplay.h"
#include "statistics.h"

using namespace std;

/* The following are related to the coursework specification */
void printName(int);
void printGamesTable(int*,int=10000);
void printFrequenceiesAndGameLenths(Player, int=10000);
void printCompetitionStatistics(Player*,GameType,int=10000);

int main()
{
	cout << play(JOE);

	return 0;

	srand(time(0));//1000);

	for(int i = 0;i<10;i++)
	{

		int statCount = 500000;

		GameType game = randomSign() < 0 ? SWITCH_JOE_FIRST : SWITCH_SID_FIRST;// ;SID_FIRST; //SWITCH_SID_FIRST;

		Player* st = competitionStatistics(game,statCount);

		printCompetitionStatistics(st,game,statCount);

		delete [] st;

		cout << endl;
	}

	return 0;
}


// Prints the name of the player
void printName(Player player)
{
	cout << '#';

	switch(player)
	{
	case SID:
		cout << "Sid playing:" << endl;
		return;
	case JOE:
		cout << "Joe playing:" << endl;
		return;
	default:
		cout << "Invalid player!" << endl;
	}

	return;
}

void printGamesTable(int* gameRatesCounter, int attempts)
{
	for(int gameRatesCounterIterator = 0; gameRatesCounterIterator<MAX_GAMES_COUNT;gameRatesCounterIterator++)	// Iterate over ammounts of throws required
	{
		if(gameRatesCounter[gameRatesCounterIterator]!=0)														// If there were more than 0 games with a specified throw count
		{
			// Print out number of throws, games count and percentage of all:
			cout << "Number of throws: " << gameRatesCounterIterator << ";\tCount: " << gameRatesCounter[gameRatesCounterIterator] << ";\tPercentage: " << 100*(double)gameRatesCounter[gameRatesCounterIterator]/attempts << '%' << endl; 
		}
	}
}

void printFrequenceiesAndGameLenths(Player player, int attempts)
{
	int* gameRatesCounter = frequenciesAndGameLengths(player, attempts);

	if(gameRatesCounter!=NULL)
	{
		printName(player);															// Print out the player's name
		printGamesTable(gameRatesCounter);
	}

	delete [] gameRatesCounter;
}

void printCompetitionStatistics(Player* stats, GameType game,int gamesCount)
{
	int joeWinsCount=0;
	int sidWinsCount=0;

	for(int gamesCounter = 0; gamesCounter<gamesCount; gamesCounter++)
	{
		if(stats[gamesCounter]==JOE)
			joeWinsCount++;
		else
			sidWinsCount++;
	}

	cout << "In " << gamesCount << " games";

	switch(game)
	{
	case JOE_FIRST:
		cout << " where Joe goes first ";
		break;
	case SID_FIRST:
		cout << " where Sid goes first ";
		break;
	case SWITCH_JOE_FIRST:
		cout << " where the looser of the last game goes first and Joe started the first game ";
		break;
	case SWITCH_SID_FIRST:
		cout << " where the looser of the last game goes first and Sid started the first game ";
		break;
	default:
		cout << " where something has gone wrong...";
	}

	cout << endl;

	cout << "->Joe wins " << 100*(double)joeWinsCount/gamesCount << "% of the games" << endl
		 << "->Sid wins " << 100*(double)sidWinsCount/gamesCount << "% of the games" << endl;
}