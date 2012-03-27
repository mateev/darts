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
//	srand(time(0));

//	srand(time(NULL));
	
	int score1 = 301;
	int score2 = 301;
	int joe = 0;

	for(int i =0;i<100000;i++)
	{
		joe += (focus100(score1,JOE) + fix50(score1) + win(JOE)) <= (focus100(score2,SID) + fix50(score2) + win(SID)) ? 1 : 0;
	}
		
	cout << (double)joe/100000;

//	cout << score2 << endl << focus100(score2,JOE) << endl << score2 <<endl;
//	cout << fix50(score2);


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
}