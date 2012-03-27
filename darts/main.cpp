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

	int j = 0;
	int j2= 0;
	int j3= 0;

	for(int i = 0;i<1000;i++)
	{
		int joeScore = 301;
		int sidScore = 301;
		j += ((focus100(joeScore,JOE) >= focus100(sidScore,SID)) ? 1 : 0);
		j2+= ((win(JOE)>=(win(SID))) ? 1 : 0);
		j3+= ((fix50(joeScore))>=(fix50(sidScore)) ? 1 :0);
	}

	cout << (double)j/1000 << endl;
	cout << (double)j2/1000<< endl;
	cout << (double)j3/1000<< endl;
	cout << (double)(j+j2+j3)/3 << endl;

	j = 0;



	return 0;


	int score1 = 301;
	int score2 = 301;
	int joe = 0;

	for(int i =0;i<100000;i++)
	{
		int f1 = focus100(score1,JOE);
		int f5 = fix50(score1);
		int w = win(JOE);

		int sum = f1+f5+w;

		joe += sum;

		score1= 301;
	}

	cout << joe;

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