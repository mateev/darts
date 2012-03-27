#include "statistics.h"

//
Player* competitionStatistics(GameType game,int gamesCount)
{
	Player* results = new Player[gamesCount];

	switch(game)
	{
	case JOE_FIRST:
		for(int gameCounter = 0; gameCounter<gamesCount; gameCounter++)
		{
			results[gameCounter] = playJoeVsSid(JOE);
		}
		break;
	case SID_FIRST:
		for(int gameCounter = 0; gameCounter<gamesCount; gameCounter++)
		{
			results[gameCounter] = playJoeVsSid(SID);
		}
		break;
	case SWITCH_JOE_FIRST:
		for(int gameCounter = 0; gameCounter<gamesCount; gameCounter++)
		{
			results[gameCounter] = (gameCounter==0 ? playJoeVsSid(JOE) : (results[gameCounter-1] == JOE ? playJoeVsSid(SID) : playJoeVsSid(JOE)));
		}
		break;
	case SWITCH_SID_FIRST:
		for(int gameCounter = 0; gameCounter<gamesCount; gameCounter++)
		{
			results[gameCounter] = (gameCounter==0 ? playJoeVsSid(SID) : (results[gameCounter-1] == JOE ? playJoeVsSid(SID) : playJoeVsSid(JOE)));
		}
		break;
	}
	return results;
}


GameStatistics* frequenciesOfGameLengths(Player player, int& numberOfRecords,int attempts)
{
	// If the player is invalid:
	if(player!=JOE && player!=SID)
		return NULL;					// Return null pointer

	bool isNewRecord;
	GameStatistics* records = NULL;

	for(int currentAttempt = 0;currentAttempt<attempts;++currentAttempt)
	{
		int intermediateValue = play(player);

		if(records==NULL)
		{
			addNewStatisticsRecord(records,numberOfRecords,intermediateValue);
		}
		else
		{
			isNewRecord = true;

			for(int i = 0;i<numberOfRecords;i++)
			{
				if(records[i].attempts==intermediateValue)
				{
					records[i].count++;
					isNewRecord = false;
					break;
				}
			}

			if(isNewRecord)
			{
				addNewStatisticsRecord(records,numberOfRecords,intermediateValue);
			}

		}


	}

	return records;
}

void addNewStatisticsRecord(GameStatistics* &records,int& numberOfRecords,int newEntry)
{
	if(records==NULL)
	{
		records = new GameStatistics[1];
		records[0].attempts = newEntry;
		records[0].count = 1;
		numberOfRecords++;

		return;
	}

	GameStatistics* temporaryValues = new GameStatistics[numberOfRecords];

	for(int indexer = 0;indexer<numberOfRecords;indexer++)
	{
		temporaryValues[indexer] = records[indexer];
	}

	delete [] records;

	++numberOfRecords;

	records = new GameStatistics[numberOfRecords];

	for(int indexer = 0;indexer<numberOfRecords-1;indexer++)
	{
		records[indexer] = temporaryValues[indexer];
	}

	records[numberOfRecords-1].attempts = newEntry;
	records[numberOfRecords-1].count = 1;

	delete [] temporaryValues;
}