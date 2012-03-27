#include <iostream>
#include <ctime>
#include <string>
#include "gameplay.h"
#include "statistics.h"

using namespace std;

/* The following are related to the coursework specification */
string name(Player);
void printGamesTable(int*,long=10000);
void printFrequenceiesOfGameLengths(Player, long=10000);
void printCompetitionStatistics(Player*,GameType,long=10000);

int main()
{
	srand(1000);

	int test[252];

	for(int i =0;i<252;i++)
		test[i]=0;

	for(int i =0;i<500000;i++)
		test[play(JOE)-1]++;

	for(int i =0;i<252;i++)
		if(test[i]!=0)
		{
			cout << i << ' ' << test[i] << endl;
		}

	printFrequenceiesOfGameLengths(JOE,500000);


	return 0;

	/*
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
	*/
}


// Prints the name of the player
string name(Player player)
{
	switch(player)
	{
	case SID:
		return "Sid";
	case JOE:
		return "Joe";
	default:
		return "Invalid player!";
	}
}

void printGamesTable(int* gameRatesCounter, long attempts)
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

void printFrequenceiesOfGameLengths(Player player, long attempts)
{
	int statisticsTableLength = 0;

	long* statisticsTable = frequenciesOfGameLengths(JOE,attempts);

	cout << "Statistics for " << name(player) << " playing by himself" << endl;

	cout << "Shots:\tCount:\tPercent:" << endl;

	for(int i = 0; i < MAX_GAMES_COUNT; i++)
	{
		if(statisticsTable[i]!=0)
		{
			cout << i << ' ' << statisticsTable[i] << endl;
		}
	}
}

void printCompetitionStatistics(Player* stats, GameType game,long gamesCount)
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