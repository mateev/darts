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
	if(player!=JOE && player!=SID)	// If the player is invalid ...
		return NULL;					// ... return null pointer

	int aGameAttempts;				// This variable will hold the result of each game played
	bool isNewRecord;				// This variable is behind the logic if we are adding a new record
	GameStatistics* records = NULL; // This variable will hold our statistics records

	for(int currentAttempt = 0;currentAttempt<attempts;++currentAttempt)			// Start counting the attempts
	{
		aGameAttempts = play(player);													// Play a game

		if(records==NULL)																// If the records are empty...
		{
			addNewStatisticsRecord(records,numberOfRecords,aGameAttempts);					// ... add the result of the game played
		}
		else																			// Or else
		{
			isNewRecord = true;																// ... assume it's a new record ...

			for(int i = 0;i<numberOfRecords;i++)											// ... go over the existing records ...
			{
				if(records[i].attempts==aGameAttempts)											// ... if that ammount of attempts exists in the records ...								
				{
					records[i].count++;																// ... increase the count by one
					isNewRecord = false;															// ... it's not a new record
					break;
				}
			}

			if(isNewRecord)																// If it's a new record ...
			{
				addNewStatisticsRecord(records,numberOfRecords,aGameAttempts);				// ... add it to the records
			}

		}

	}

	return records;				// Return the records
}

void addNewStatisticsRecord(GameStatistics* &records,int& numberOfRecords,int newEntry)
{
	if(records==NULL)						// If the records are empty
	{
		records = new GameStatistics[1];		// ... create them ...
		records[0].attempts = newEntry;			// ... add the new entry ...
		records[0].count = 1;
		numberOfRecords++;						// ... increase the count

		return;
	}

	GameStatistics* temporaryValues = new GameStatistics[numberOfRecords];		// This will hold the records when copying

	for(int indexer = 0;indexer<numberOfRecords;indexer++)						//	This loop copies the records to the temporary holder
	{
		temporaryValues[indexer] = records[indexer];
	}

	delete [] records;															// Delete the original records

	++numberOfRecords;															// Increase the count

	records = new GameStatistics[numberOfRecords];								// Re-initialize records with the new counter

	for(int indexer = 0;indexer<numberOfRecords-1;indexer++)					// Restore the records from the temporary holder
	{
		records[indexer] = temporaryValues[indexer];
	}

	records[numberOfRecords-1].attempts = newEntry;								// Add the new entry
	records[numberOfRecords-1].count = 1;

	delete [] temporaryValues;													// Clean up
}