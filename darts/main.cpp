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

void xswap(int* first, int* second)
{
	*first ^= *second;
	*second ^=* first;
	*first ^=* second;
}

void game(GameType type = JOE_FIRST,int tries = 10000)
{
	srand(time(0));

	Player first;// = (type==JOE_FIRST ? JOE : SID);
	Player second;// = (first==JOE ? SID :JOE);

	int firstWins = 0;
	int secondWins = 0;


	if(type!=SWITCH)
		first = (type==JOE_FIRST ? JOE : SID);
	else
		first = randomSign() < 0 ? JOE : SID;
	
	second = (first==JOE ? SID :JOE);		

	for(int tr = 0;tr<tries;tr++)
	{
		int firstPlay  = play(first);
		int secondPlay = play(second);

		if(firstPlay<=secondPlay)
		{
			firstWins++;
		}
		else
		{
			secondWins++;
		}

		if(type==SWITCH)
		{
			swap(first,second);
			swap(firstWins,secondWins);
		}

	}

	if(first==JOE)
		cout << (double)firstWins*100/(tries) << endl;
	else
		cout << (double)secondWins*100/(tries) << endl;
}

void pl(int tries = 10000)
{
	srand(time(0));

	Player first = JOE;
	Player second = SID;

	int firstWins = 0;
	int secondWins = 0;

	for(int tr = 0;tr<tries;tr++)
	{
		int firstPlay  = play(first);
		int secondPlay = play(second);

		if(firstPlay<=secondPlay)
		{
			firstWins++;
		}
		else
			secondWins++;

	}

	if(first==JOE)
		cout << (double)firstWins*100/(tries) << endl;
	else
		cout << (double)secondWins*100/(tries) << endl;
}

int main()
{
//	pl();

	game(SWITCH);

	return 0;

	int joeScore = 301;
	int sidScore = 301;

	int joe = 0;
	int sid = 0;

	long joeWins = 0;
	long sidWins = 0;

	int all = 1000;

	for(int i = 0;i<all;i++)
	{
		joe = focus100(joeScore,JOE) + fix50(joeScore) + win(JOE);
		sid = focus100(sidScore,SID) + fix50(sidScore) + win(SID);


		if (joe <= sid)
		{
			cout << '#';
			joeWins++; 
		}
		else
			sidWins++;

		cout << joe << ' ' << sid << endl;

		joeScore = sidScore = 301;
	}
	
	cout << (double)joeWins*100/all << endl << joeWins+sidWins;

	//cout << joeWins << endl << sidWins << endl;

//	cout << joe << ' ' << sid << endl
//		<< joe+1<< ' ' << sid << endl;

//	cout << ((joe+1) < sid);

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