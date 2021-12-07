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
void computerRoundWin();
void playerRoundWin();
void drawRound();

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

bool gameLogic[5][5] = {
	{false, false, true, true, false},
	{true, false, false, false, true},
	{false, true, false, true, false},
	{false, true, false, false, true},
	{true, false, true, false, false}
};

int main() {
	while (progExit == false)
	{
		titleMenu();
	}

	return 0;
}

void titleMenu() {
	gameExit = false;
	playerChoice = 0;
	playerScore = 0;
	computerChoice = 0;
	computerScore = 0;
	curRound = 1;

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
		game(3);
		break;
	case 2: //best of 5
		game(5);
		break;
	case 3: //best of user defined
		cout << "Enter Number of Rounds: ";
		cin >> userRound;
		game(userRound);
		break;
	case 4: //endless mode
		endlessMode = true;
		game(0);
		break;
	case 5: //exit
		progExit = true;
		break;
	default:
		titleMenu();
		break;
	}
}
void printRoundScore() {
	cout << "[ Round Number: " << curRound << " ]" << endl;
	cout << "[ Player Score: " << playerScore << " || " << "Computer Score: " << computerScore << " ]" << endl << endl;
}

void printCurInputs() {
	cout << "--------------------------" << endl;
	cout << "Player Input: " << gameChoices[playerChoice] << endl;
	cout << "Computer Input: " << gameChoices[computerChoice] << endl;
	cout << "--------------------------" << endl << endl;
}

void playerRoundWin() {
	printRoundScore();
	printCurInputs();
	cout << "[ Player Wins!! ]" << endl << endl;
	system("pause");
	playerScore++;
	curRound++;
	system("CLS");
}

void computerRoundWin() {
	printRoundScore();
	printCurInputs();
	cout << "[ Computer Wins!! ]" << endl << endl;
	system("pause");
	computerScore++;
	curRound++;
	system("CLS");
}

void drawRound() {
	printRoundScore();
	printCurInputs();
	cout << "[ !!Draw!! ]" << endl << endl;
	system("pause");
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

			if (playerChoice == computerChoice && gameExit == false)
			{
				drawRound();
			}
			else
			{
				gameWinner = victDecider(playerChoice, computerChoice);

				//player wins
				if (gameWinner == true && gameExit == false)
				{
					playerRoundWin();
				}
				//computer wins
				else if (gameWinner == false && gameExit == false)
				{
					computerRoundWin();
				}
				//exit
				else
				{
					gameExit = true;
					titleMenu();
				}
			}
		}
	}
	else
	{
		while (curRound <= roundMax && gameExit == false)
		{
			printRoundScore();
			gameInput();
			if (playerChoice == 5)
			{
				cout << "";
			}
			if (playerChoice == computerChoice && gameExit == false)
			{
				drawRound();
			}
			else
			{
				gameWinner = victDecider(playerChoice, computerChoice);

				//player wins
				if (gameWinner == true && gameExit == false)
				{
					playerRoundWin();
				}
				//computer wins
				else if (gameWinner == false && gameExit == false)
				{
					computerRoundWin();
				}
				//exit
				else
				{
					cout << "Exit" << endl;
					gameExit = true;
				}
			}
		}
		if (curRound >= roundMax)
		{
			if (playerScore == computerScore)
			{
				curRound--;
			}
			else if (playerScore > computerScore)
			{
				system("CLS");
				curRound--;
				printRoundScore();
				cout << "-----------------------------" << endl;
				cout << "[ Player Wins the Game!! ]" << endl;
				cout << "-----------------------------" << endl << endl;
				system("pause");
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
			}
		}
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
	cout << "--------------------------" << endl;

	if (playerChoice == 5)
	{
		helpMenu();
		while (playerChoice == 5)
		{
			printRoundScore();
			cout << "----------------------------------" << endl;
			cout << "Enter [6] for help or [7] to quit" << endl;
			cout << "----------------------------------" << endl;
			cout << "Enter Input: ";
			cin >> playerChoice;
			playerChoice--;
			cout << "--------------------------" << endl;

			if (playerChoice == 5)
			{
				helpMenu();
			}
		}

	}
	if (playerChoice == 6)
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

