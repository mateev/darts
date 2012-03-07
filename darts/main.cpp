#include <iostream>
#include <ctime>

typedef unsigned short Player;

/* The following hold Joe and Sid's bull success rates */
const Player JOE = 70;
const Player SID = 72;

enum GameType
{
	JOE_FIRST = 0,
	SID_FIRST,
	SWITCH_JOE_FIRST,
	SWITCH_SID_FIRST
};

const unsigned short MAX_GAMES_COUNT = 301 - 50;
const unsigned short MIN_GAMES_COUNT = 7;

using namespace std;

int score[21] = {20, 1, 18, 4, 13, 6, 10, 15, 2, 17, 3, 19, 7, 16, 8, 11, 14, 9, 12, 5, 20};

/* The following handle points awarding when a darts hits a board */
int throwBull(Player);					// This tries to hit a bull and returns score; paramater is bull hit success percentage
int hitAttemptScore(int);			// This tries to hit a number and returns the result

/* The following handle score-array traversal */
int returnScoreOfNeighbour(int);	// This returns the points of a neighbour of a target; the paramater is the target
int randomSign();

/* The Following return the number of attempts */
int tryToLowerToBelow100(int&,Player);		// This tries to lower the score to under 100; score is passed as parameter
int tryToLowerTo70Below100(int&);	// This tries to lower the score to 50; paramater is current score
int tryToLowerBelow70To50(int);		// This tries to lower the score to 50 if it is under 70; paramater is current score
int tryToWin(int);						// This tries to hit the bull

/* The following play as different players */
int play(Player);						//returns attempts until win
int playJoe();						// plays as joe
int playSid();						// plays as sid
Player playJoeVsSid(Player=JOE);		// This plays a Joe vs Sid game, asuming Joe plays first

/* The following are related to the coursework specification */
void printName(int);
int* frequenciesAndGameLengths(Player,int=10000);	// Prints out number of throws, games count and percentage in a table; return the table itself
//double playJoeVsSid(int=10000);
void printGamesTable(int*,int=10000);
void printFrequenceiesAndGameLenths(Player, int=10000);
Player* competitionStatistics(GameType,int=10000);
void printCompetitionStatistics(Player*,GameType,int=10000);

int main()
{
			srand(1000);
/*	for(int i =0;i<10000;i++)
	{
		cout << ((playJoeVsSid()==JOE) ? "Joe" : "Sid") << endl;
	}
*/
	int statCount = 1000;

	GameType game = SWITCH_SID_FIRST;

	Player* st = competitionStatistics(game,statCount);

	printCompetitionStatistics(st,game,statCount);

	delete [] st;

	return 0;
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


// This plays a Joe vs Sid game
Player playJoeVsSid(Player firstPlayer)
{
	Player secondPlayer = firstPlayer == JOE ? SID : JOE;			// If the first player is Joe, the second will be Sid and vice versa

	int firstPlayerGame = play(firstPlayer);						// First player plays by himself
	int secondPlayerGame = play(secondPlayer);						// Second player plays by himself

	if(firstPlayerGame > secondPlayerGame)						// If first player's attempts count is bigger than the second player's
	{
		return secondPlayer;										// ... first player looses
	}
	else 
	{
		return firstPlayer;											// ... second player looses
	}
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

int* frequenciesAndGameLengths(Player player,int attempts)
{
	// If the player is invalid:
	if(player!=JOE && player!=SID)
		return NULL;					// Return null pointer

	int* gameRatesCounter = new int[MAX_GAMES_COUNT];							// Allocate memory for the table

	for(int gamesCounter = 0; gamesCounter<MAX_GAMES_COUNT; gamesCounter++)		// Fill all members with 0
		gameRatesCounter[gamesCounter]=0;

	for(int gamesCounter = 0; gamesCounter<attempts;gamesCounter++)				// Play the game attempts-times
	{

		int currentGames = play(player);											// ... record how many throws did the current game take
		gameRatesCounter[currentGames]++;											// ... increase the counter for that ammount of throws
	}

	return gameRatesCounter;							// All went good
}

// plays as joe
int playJoe()
{
	return play(JOE);
}

// plays as sid
int playSid()
{
	return play(SID);
}

// Returns attempts until win
int play(Player bullSuccessRate)
{
	int attempts = 0;	// This variable counts the attempts it took
	int score = 301;	// This variable holds the score

	bool playing = true;// This variable controls if the game is on or not

	while(playing)		// while the game is on
	{
		if(score>100)		// if score is above 100
			attempts+=tryToLowerToBelow100(score,bullSuccessRate);// try to lower below 100 and record how long it took
		else if (score<100)	// else if score is below 100
		{
			if(score>70)	// if score is above 70
				attempts+=tryToLowerTo70Below100(score);	// try to lower to 70 and record how long it took
			else if(score>50)			// else
			{
				attempts+=tryToLowerBelow70To50(score);		// try to lower to 50
				score = 50;									// score has been lowered to 50, so the variable score:=50
			}

			if(score==50) // else
			{
				attempts+=tryToWin(bullSuccessRate);			// try to win
				playing = false;								// playing:=false
			}

		}
	}// loop ends here

	return attempts;
}

// This tries to lower the score to under 100; score is passed as parameter
int tryToLowerToBelow100(int& currentScore, Player successPercentage)
{
	int attemptsCount = 0;

	int score = currentScore;

	while(score>=100)
	{
		score -= throwBull(successPercentage);
		attemptsCount++;
	}

	currentScore = score;
	return attemptsCount;
}

// This tries to hit the bull
int tryToWin(int successPercentage)
{
	int attemptsCount = 0;

	do
	{
		attemptsCount++;
	}
	while(throwBull(successPercentage)!=50);

	return attemptsCount;
}

//	This returns the points of a neighbour of a target; the paramater is the target
int returnScoreOfNeighbour(int target)
{
	if(target==20)							// If target is 20 ...
	{
		return randomSign()<0 ? 1 : 5;		// ... choose one of the 20s at random
	}
	else									// Or else ...
	{
		for(int i = 0;i<21;i++)					// ... find the target in the array, add +/- 1 to the index and return the value
			if(score[i]==target)
				return score[i+randomSign()];
	}

	return -1;	// Error somewhere
}

//	This function attempts to hit a target and returns if it has hit or not
int hitAttemptScore(int target)
{
	/* Try to hit */
	int successCalculator;

	do
	{
		successCalculator = rand();
	}
	while(successCalculator>32700);

	successCalculator %= 100;
	/**/

	// If it is under 80% ...
	if(100-successCalculator<80)
		// ... return target
		return target;
	// Else ...
	else
	{
		// Return one of the target's neighbours
		return returnScoreOfNeighbour(target);
	}

}

//	This function returns the attempts it took to lower the score to 50
int tryToLowerBelow70To50(int currentScore)
{
	int attemptsCount = 1;													// This varible counts the attempts it took

	int hitAttemptScoreValue = hitAttemptScore(currentScore-50);			// This variable holds the result of the attempt
																			//	to hit (currentScore-50)

	if(hitAttemptScoreValue!=currentScore-50)								// If the hit was not successfull...
	{
		if(currentScore-hitAttemptScoreValue<50)								// ... and (score-(what we've hit))<50
			attemptsCount += tryToLowerBelow70To50(currentScore);					// ... try to hit (20-score) again ...
		else if(currentScore-hitAttemptScoreValue>50)							// ... and (score-(what we've hit))>50 ...
			attemptsCount += tryToLowerBelow70To50(currentScore-hitAttemptScoreValue);// ... try to hit (score-what we've hit) again ...
	}

	return attemptsCount;													// Return attempts count :-]
}

//	This function tries to lower the score to less than 70
int tryToLowerTo70Below100(int& currentScore)
{
	int attemptsCount = 0;													// Counts the attempts it took

	int score = currentScore;												// Store currentScore as score

	while(score>70)															// While score>70 ...
		score -= hitAttemptScore(20);											// ... throw at 20

	currentScore = score;													// Save the reduced score
	return attemptsCount;													// Return the attempts it took
}

//	This function tries to throw the bull
int throwBull(Player successPercentage)
{
	// Generate a number from 0-100 to figure out if bull hit was a success

	int successCalculator;

	do
	{
		successCalculator = rand();
	}
	while(successCalculator>32700);

	// Get success percentage
	successCalculator %= 100;

	// [TODO: Something not right here!!!]
	if(successCalculator < 70)		// If it is under the success percentage ... // successPercentage is never used!
		return 50;						// ... bull is hit and we return score of 50


	/* TODO: Investigate if variable reuse is bad in here */
	// Generate a number from 0-21 to pick a random section of the board, *other* than the bull
	successCalculator = rand() % 21; /* TODO: See if a variant of [1] needs to be done for this too */
	
	// ... return the points that this section awards
	return score[successCalculator];
}

// This generates a random sign
int randomSign()
{
	return rand()%2 == 0 ? -1 : 1;
}

