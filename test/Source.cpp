#include <iostream>
#include <random>

using namespace std;

void titleMenu();
void game(int roundMax);
void gameInput();
int randomNumber();
bool victDecider(int playerChoice, int computerChoice);

int playerChoice = 0;
int playerScore = 0;
int computerChoice = 0;
int computerScore = 0;
bool gameOutcome = false;
bool gameWinner = false;
bool gameExit = false;


string gameChoices[5] = { "Rock", "Paper", "Scissors", "Lizard", "Spock" };

bool gameLogic[5][5] = {
	{false, false, true, true, false},
	{true, false, false, false, true},
	{false, true, false, true, false},
	{false, true, false, false, true},
	{true, false, true, false, false}
};

int main() {
	titleMenu();
	return 0;
}

void titleMenu() {
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
		game(3);
		break;
	case 3: //best of user defined
		cout << "Enter Number of Rounds: ";
		cin >> userRound;
		game(userRound);
		break;
	case 4: //endless mode
		//tbd
		break;
	case 5: //exit
		gameExit = true;
		break;
	default:
		titleMenu();
		break;
	}
}

void game(int roundMax) {

	int curRound = 1;

	while (curRound <= roundMax && gameExit == false)
	{
		cout << "Round Number: " << curRound << endl;
		cout << "Player Score: " << playerScore << " || " << "Computer Score: " << computerScore << endl << endl;
		gameInput();

		if (playerChoice == computerChoice && gameExit == false)
		{
			cout << "Draw" << endl;
			system("pause");
			system("CLS");
		}
		else
		{
			gameWinner = victDecider(playerChoice, computerChoice);

			//player wins
			if (gameWinner == true && gameExit == false)
			{
				cout << "Player Input: " << gameChoices[playerChoice] << endl;
				cout << "Computer Input: " << gameChoices[computerChoice] << endl;
				cout << "Player Wins" << endl;
				system("pause");
				playerScore++;
				curRound++;
				system("CLS");
			}
			//computer wins
			else if (gameWinner == false && gameExit == false)
			{
				cout << "Player Input: " << gameChoices[playerChoice] << endl;
				cout << "Computer Input: " << gameChoices[computerChoice] << endl;
				cout << "Computer Wins" << endl;
				system("pause");
				computerScore++;
				curRound++;
				system("CLS");
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
			cout << "Player Score: " << playerScore << " || " << "Computer Score: " << computerScore << endl << endl;
			cout << "Player Wins!!" << endl;
		}
		else
		{
			cout << "Player Score: " << playerScore << " || " << "Computer Score: " << computerScore << endl << endl;
			cout << "Computer Wins!!" << endl;
		}
	}

}

void gameInput() {
	cout << "Enter Input: ";
	cin >> playerChoice;

	if (playerChoice == 6)
	{
		gameExit = true;
	}

	computerChoice = randomNumber();

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

