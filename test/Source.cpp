#include <iostream>
#include <random>

using namespace std;


void titleMenu();
void game(int roundMax);
void gameInput();
int randomNumber();
bool victDecider(int playerChoice, int computerChoice);
void helpMenu();
void printRoundScore();
void printCurInputs();
void roundWin(int playerChoice, int compChoice);
void resetGameVars();
void overallWinner(int compScore, int playerScore);

//define all the global variable
int playerChoice = 0;
int playerScore = 0;
int computerChoice = 0;
int computerScore = 0;
int curRound = 1;
bool gameOutcome = false;
bool gameWinner = false;
bool gameExit = false;
bool progExit = false;
bool endlessMode = false;


string gameChoices[5] = { "Rock", "Paper", "Scissors", "Lizard", "Spock" };

//define the overall game logic (with all the draw conditions as a loss as to not confuse the user in the condition the draw evaluation fails)
bool gameLogic[5][5] = {
	{false, false, true, true, false},
	{true, false, false, false, true},
	{false, true, false, true, false},
	{false, true, false, false, true},
	{true, false, true, false, false}
};

int main() {
	//start the program in a while loop to allow the user to exit to the menu multiple times without exiting the program
	while (progExit == false)
	{
		titleMenu();
	}

	return 0;
}

void resetGameVars() {
	//set all the game sepecific variables to allow the user to play multiple games without restarting the program
	playerChoice = 0;
	playerScore = 0;
	computerChoice = 0;
	computerScore = 0;
	curRound = 1;
}

void titleMenu() {
	//reset game specific variables
	resetGameVars();

	//clear the console
	system("CLS");

	//define the local menu variables
	int menuSelect = 0;
	int userRound = 0;

	//print the menu options
	cout << "[ [1] Best of 3    ]" << endl;
	cout << "[ [2] Best of 5    ]" << endl;
	cout << "[ [3] Best of X    ]" << endl;
	cout << "[ [4] Endless Mode ]" << endl;
	cout << "[ [5] Quit         ]" << endl << endl;
	cout << "Selection: ";

	//take the user input into the menu select variable
	cin >> menuSelect;
	cout << endl;

	//use the menu select variable to select an option from the switch
	switch (menuSelect)
	{
	case 1: //best of 3
		gameExit = false;
		game(3);
		break;
	case 2: //best of 5
		gameExit = false;
		game(5);
		break;
	case 3: //best of user defined
		gameExit = false;
		cout << "Enter Number of Rounds: ";
		cin >> userRound;
		game(userRound);
		break;
	case 4: //endless mode
		gameExit = false;
		endlessMode = true;
		game(0);
		break;
	case 5: //exit
		gameExit = true;
		progExit = true;
		break;
	default: //reset the menu in case of an invalid input
		cout << "[ !!Invalid Input!! ]" << endl;
		system("pause");
		titleMenu();
		break;
	}
}
void printRoundScore() {
	//this function prints the current round number and the current scores
	cout << "[ Round Number: " << curRound << " ]" << endl;
	cout << "[ Player Score: " << playerScore << " || " << "Computer Score: " << computerScore << " ]" << endl << endl;
}

void printCurInputs() {
	//this function prints the current round inputs from the user and the computer
	cout << "--------------------------" << endl;
	cout << "Player Input: " << gameChoices[playerChoice] << endl;
	cout << "Computer Input: " << gameChoices[computerChoice] << endl;
	cout << "--------------------------" << endl << endl;
}

void roundWin(int playerChoice, int compChoice) {
	//this function prints the individual round victor

	//print the round score and current inputs to keep the visuals consistent
	printRoundScore();
	printCurInputs();
	
	//if (playerChoice == 5)
	//{
	//	cout << "";
	//}

	if (playerChoice == compChoice)
	{

		cout << "[ !!Draw!! ]" << endl << endl;

		system("pause");
		system("CLS");
	}
	else
	{
		gameWinner = victDecider(playerChoice, computerChoice);

		//

		if (gameWinner == true)
		{
			cout << "[ Player Wins!! ]" << endl << endl;

			system("pause");

			playerScore++;

		}
		else
		{
			cout << "[ Computer Wins!! ]" << endl << endl;

			system("pause");

			computerScore++;
		}
		curRound++;
	}

	system("CLS");
}

void game(int roundMax) {
	system("CLS");
	if (endlessMode == true && gameExit == false)
	{
		while (endlessMode == true && gameExit == false)
		{
			printRoundScore();
			gameInput();

			if (gameExit == false)
			{
				roundWin(playerChoice, computerChoice);
			}
			else
			{
				gameExit = true;
				titleMenu();
			}
		}
	}
	else
	{

		while (curRound <= roundMax && gameExit == false)
		{
			printRoundScore();
			gameInput();

			if (gameExit == false)
			{
				roundWin(playerChoice, computerChoice);
			}
			else
			{
				gameExit = true;
				titleMenu();
			}
		}
		if (curRound >= roundMax)
		{
			overallWinner(computerScore, playerScore);
		}
		if (playerScore == roundMax - 1)
		{
			overallWinner(computerScore, roundMax);
		}
		if (computerScore == roundMax - 1)
		{
			overallWinner(roundMax, playerScore);
		}

	}



}
void overallWinner(int compScore, int playerScore) {

	if (playerScore == compScore)
	{
		curRound--;
	}
	else if (playerScore > compScore)
	{
		system("CLS");
		curRound--;
		printRoundScore();
		cout << "-----------------------------" << endl;
		cout << "[ Player Wins the Game!! ]" << endl;
		cout << "-----------------------------" << endl << endl;
		system("pause");
		titleMenu();
	}
	else
	{
		system("CLS");
		curRound--;
		printRoundScore();
		cout << "-----------------------------" << endl;
		cout << "[ Computer Wins the Game!! ]" << endl;
		cout << "-----------------------------" << endl << endl;
		system("pause");
		titleMenu();
	}
}

//[0]Rock [1]Paper [2]Scissors [3]Lizard [4]Spock [5]Help [6]Quit
// 1       2        3           4         5        6       7
void gameInput() {
	cout << "---------------------------------" << endl;
	cout << "Enter [6] for help or [7] to quit" << endl;
	cout << "---------------------------------" << endl;
	cout << "Enter Input: ";
	cin >> playerChoice;
	playerChoice--;
	cout << "---------------------------------" << endl;

	if (playerChoice > 6 || playerChoice < 0)
	{
		cout << endl << "[ !!Invalid Input!! ]" << endl << endl;
		system("pause");
		while (playerChoice > 6 || playerChoice < 0)
		{
			system("CLS");
			printRoundScore();
			gameInput();
		}
	}
	else if (playerChoice == 5)
	{
		helpMenu();
		while (playerChoice == 5)
		{
			printRoundScore();
			gameInput();

			if (playerChoice == 5)
			{
				helpMenu();
			}
		}

	}
	else if (playerChoice == 6)
	{
		gameExit = true;
	}

	computerChoice = randomNumber();
	system("CLS");

}

int randomNumber() {
	random_device random;
	mt19937 ranGen(random());
	uniform_int_distribution<int> uniq(0, 4);
	int r_int = uniq(ranGen);

	return r_int;
}

bool victDecider(int playerChoice, int computerChoice)
{
	gameOutcome = gameLogic[playerChoice][computerChoice];

	return gameOutcome;
}

void helpMenu() {
	system("CLS");
	printRoundScore();
	cout << "--------------------------" << endl;
	cout << "Game Actions: " << endl;
	cout << "--------------------------" << endl;
	cout << "[1] Rock " << endl;
	cout << "[2] Paper " << endl;
	cout << "[3] Scissors " << endl;
	cout << "[4] Lizard " << endl;
	cout << "[5] Spock " << endl;
	cout << "--------------------------" << endl;
	cout << "Program Actions: " << endl;
	cout << "--------------------------" << endl;
	cout << "[6] Help " << endl;
	cout << "[7] Exit " << endl << endl;
	system("pause");
	system("CLS");
}

