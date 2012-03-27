#include <iostream>
#include <ctime>
#include <string>
#include "gameplay.h"
#include "statistics.h"

using namespace std;

/* The following print statistics */
string name(Player);
void printFrequenceiesOfGameLengths(Player, long=10000);
void printJoeVsSid(long = 10000);

int main()
{
	srand(time(0));

	long sampleSize = 0;

	cout << "Enter sample size:";
	cin >> sampleSize;

	printFrequenceiesOfGameLengths(JOE,sampleSize);

	cout << endl;

	printJoeVsSid(sampleSize);


	return 0;

}

void printJoeVsSid(long gamesCount)
{
	double mean = 0;		//	This variable will hold the mean value for each rule
	double currentRun;		//	This variable will hold the percentage for each run

	cout << "#Joe Vs Sid - estimates of Joe's Percentage Success Rate" << endl;

	cout << "Rule\t";

	for(int runDisplay = 0;runDisplay<5;runDisplay++)
	{
		cout << "Run " << runDisplay << '\t';
	}

	cout << "Mean" << endl;

	for(int rule = 1;rule <= 3; rule++)
	{
		mean = 0;			//	Reset mean value

		cout << rule << '\t';

		for(int run = 0;run<5;run++)
		{
			currentRun = joeGames((GameType)(rule),gamesCount);
			mean+=currentRun;
			cout << currentRun << '\t';
		}

		cout << mean/5 << endl;

	}

	cout << endl << "Rules:" << endl
			<< "\t1. Joe throws first" << endl
			<< "\t2. Sid throws first" << endl
			<< "\t3. Toss a coin to start, loser starts next" << endl;
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
	int allShotsCount = 0;
	int allAttemptsCount = 0;
	double allPercentCount = 0;

	long* statisticsTable = frequenciesOfGameLengths(JOE,attempts);

	cout << "#Statistics for " << name(player) << " playing by himself" << endl;

	cout << "Shots:\tGames:\tPercent:" << endl;

	for(int i = 0; i < MAX_GAMES_COUNT; i++)
	{
		if(statisticsTable[i]!=0)
		{
			allShotsCount += i+1;
			allAttemptsCount += statisticsTable[i];
			allPercentCount += ((double)statisticsTable[i]/attempts)*100;
			cout << i+1 << '\t' << statisticsTable[i] << '\t' << ((double)statisticsTable[i]/attempts)*100 << '%' << endl;
		}
	}

	for(int i =0; i < 25; i++) cout << '=';

	cout << endl << allShotsCount << '\t' << allAttemptsCount << '\t' << allPercentCount << '%' << endl;
}

