#include <iostream>
#include <ctime>
#include <string>
#include "gameplay.h"
#include "statistics.h"

using namespace std;

/* The following are related to the coursework specification */
string name(Player);
void printFrequenceiesOfGameLengths(Player, long=10000);

void printCompetitionStatistics(Player*,GameType,long=10000);
void printCompetitionStatsJoeFirst(long=10000);

int main()
{
	srand(time(0));

	cout << "Joe Vs Sid - estimates of Joe's Percentage Success Rate" << endl;

	cout << "Rule\t";

	for(int runDisplay = 0;runDisplay<5;runDisplay++)
	{
		cout << "Run " << runDisplay << '\t';
	}

	cout << "Mean" << endl;

	for(int rule = 1;rule <= 3; rule++)
	{
		cout << rule << '\t';

		double mean = 0;
		double currentRun = 0;

		for(int run = 0;run<5;run++)
		{
			currentRun = joeGames((GameType)(rule));
			mean+=currentRun;
			cout << currentRun << '\t';
		}

		cout << mean/5 << endl;

	}

	cout << "Rules:" << endl
			<< "1. Joe throws first" << endl
			<< "2. Sid throws first" << endl
			<< "3. Toss a coin to start, loser starts next" << endl;

	return 0;

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


void printFrequenceiesOfGameLengths(Player player, long attempts)
{
	int statisticsTableLength = 0;

	long* statisticsTable = frequenciesOfGameLengths(JOE,attempts);

	cout << "#Statistics for " << name(player) << " playing by himself" << endl;

	cout << "Shots:\tCount:\tPercent:" << endl;

	for(int i = 0; i < MAX_GAMES_COUNT; i++)
	{
		if(statisticsTable[i]!=0)
		{
			cout << i+1 << '\t' << statisticsTable[i] << '\t' << ((double)statisticsTable[i]/attempts)*100 << '%' << endl;
		}
	}
}

void printCompetitionStatsJoeFirst(long attempts)
{
	Player* stats = competitionStatistics(SID_FIRST,attempts);

	printCompetitionStatistics(stats,SID_FIRST,attempts);

	delete [] stats;
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

	/*
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

	cout << "->Joe wins " << 100*(double)joeWinsCount/gamesCount << "% of the games" << endl;
//		 << "->Sid wins " << 100*(double)sidWinsCount/gamesCount << "% of the games" << endl;
	*/
}