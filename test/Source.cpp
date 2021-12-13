
//Oliver Bond : P2530924

//[0]Rock [1]Paper [2]Scissors [3]Lizard [4]Spock [5]Help [6]Quit
// 1       2        3           4         5        6       7

#include <iostream>
#include <random>

using namespace std;

//define function forward declarations
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

//define all the global variables
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

//define all possible game choices in an array so the program can print what selections the player and the computer made
string gameChoices[5] = { "Rock", "Paper", "Scissors", "Lizard", "Spock" };

//define the overall game logic (with all the draw conditions as a loss as to not confuse the user in the condition the draw evaluation fails)
bool gameLogic[5][5] = {
	{false, false, true, true, false},
	{true, false, false, false, true},
	{false, true, false, true, false},
	{false, true, false, false, true},
	{true, false, true, false, false}
};

//this is an additional 2d array that has flavour text in the same positions as the game logic array to allow flavour text to be printed at the
//end of each round
string flavorText[5][5] = {
	{"Null","Paper Covers Rock","Rock Crushes Scissors","Rock Crushes Lizard","Spock Vaporises Rock"},
	{"Paper Covers Rock","Null","Scissors Cuts Paper","Lizard Eats Paper","Paper Disproves Spock"},
	{"Rock Crushes Scissors","Scissors Cuts Paper","Null","Scissors Decapitates Lizard","Spock Smashes Scissors"},
	{"Rock Crushes Lizard","Lizard Eats Paper","Scissors Decapitates Lizard","Null","Lizard Poisons Spock"},
	{"Spock Vaporises Rock","Paper Disproves Spock","Spock Smashes Scissors","Lizard Poisons Spock","Null"}
};

int main() {

	//start the program in a while loop to allow the user to exit to the menu multiple times without exiting the program
	while (progExit == false)
	{
		//call the title menu function
		titleMenu();
	}
	return 0;
}

//this function prints a menu to allow multiple different modes, and to give the user a clean exit option
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

	/*
	while the user input is greater than 6 or less than 1 or if the data type entered doesnt match the menu select variable:
		tell the user their input was invalid
		clear the error state flags caused by the type mismatch
		use cin.ignore(256, '\n') to prevent an unintended loop by removing the first value of characters from the input sequence or until the defined delim is reached
		pause the console to allow the user to read the error message
		call the title menu function
	*/
	while (menuSelect > 6 || menuSelect < 1 || cin.fail())
	{
		cout << "[!! Invalid Input !!]" << endl << endl;
		cin.clear();
		cin.ignore(256, '\n');
		system("pause");
		titleMenu();
	}

	/*
	use the menu select variable to select an option from the switch:
		case 1 - best of 3:
			reset the game exit boolean to ensure the game doesn't exit to menu
			call the game function, passing 3 as the number of rounds

		case 2 - best of 5:
			reset the game exit boolean to ensure the game doesn't exit to menu
			call the game function, passing 5 as the number of rounds

		case 3 - best of user defined:
			reset the game exit boolean to ensure the game doesn't exit to menu
			get the user to input the number of rounds they wish to play
			call the game function, passing the user defined number of rounds

		case 4 - endless mode:
			reset the game exit boolean to ensure the game doesn't exit to menu
			set the endless boolean to true to indicate the player wants endless rounds
			call the game function, passing 0 as the number of rounds as in endless mode this value gets ignored

		case 5 - exit:
			set both game exit and program exit booleans to true to allow the user to exit the program

		default - reset the menu in case of an invalid input:
			notify the user of the general error type
			pause the console to allow the user to understand
			Clears the error state flags caused by the type mismatch using cin.clear()
			use cin.ignore(256, '\n') to prevent an unintended loop by removing the first value of characters from the input sequence or until the defined delim is reached
	*/
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
		cout << "[!! Invalid Input - Input Validation Error !!]" << endl << endl;
		system("pause");
		cin.clear();
		cin.ignore(256, '\n');
		break;
	}
}

//this function controls starting the game, starting each round, and calling of all game related functions
void game(int roundMax) {
	//clear the console at the beginning of the game and at the start of each round
	system("CLS");

	//if the player has started the game in endless mode and the game exit boolean equals false
	if (endlessMode == true && gameExit == false)
	{
		/*
		while endless mode equals true:
		call a function that prints the current round and the current score
		calls a function that gets the player input and generates the computers input

		if game exit boolean equals false calculate the round winner based on the user and computer input:
			call a function that determines who the round victor is when passed the player and computer input

		if the game exit boolean equals true:
			set the game exit boolean to true
			call the title menu function
		*/
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
	//if the user selected any other game mode except endless mode
	else
	{

		/*
		while the current round is less than or equal to the maximum round integer passed into the game function, and the game exit boolean equals false:
		call a function that prints the current round number and the current score
		call a function that gets the user input and generates the computer input

		if the game exit boolean equals false
			call a function that determines who the round victor is when passed the player and computer input

		if the game exit boolean equals true
			set the game exit boolean to true
			call the title menu function
		*/
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
		/*if the current round is greater than or equal to the maximum round passed into the game function:
		call a function that decides the overall winner by being passed the computer and player score variable*/
		if (curRound >= roundMax)
		{
			overallWinner(computerScore, playerScore);
		}

	}

}

//this function controls all of the turn inputs for the game function
void gameInput() {
	cout << "---------------------------------" << endl;
	cout << "Enter [6] for help or [7] to quit" << endl;
	cout << "---------------------------------" << endl;
	cout << "Enter Input: ";
	cin >> playerChoice;
	playerChoice--;
	cout << "---------------------------------" << endl;

	if (playerChoice > 6 || playerChoice < 0 || cin.fail())
	{
		cout << endl << "[ !!Invalid Input!! ]" << endl << endl;
		cin.clear(); //Clears the error state flags caused by the type mismatch
		cin.ignore(256, '\n');//used to prevent an unintended loop by removing the first value of characters from the input sequence or until the defined delim is reached
		system("pause");
		system("CLS");
		printRoundScore();
		gameInput();

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

//this function sets all the game sepecific variables to their default values to allow the user to play multiple games without restarting the program
void resetGameVars() {
	playerChoice = 0;
	playerScore = 0;
	computerChoice = 0;
	computerScore = 0;
	curRound = 1;
}

//this function prints the current round number and the current scores
void printRoundScore() {
	cout << "[ Round Number: " << curRound << " ]" << endl;
	cout << "[ Player Score: " << playerScore << " || " << "Computer Score: " << computerScore << " ]" << endl << endl;
}

//this function prints the current round inputs from the user and the computer as a string using the game choices array
void printCurInputs() {
	cout << "--------------------------" << endl;
	cout << "Player Input: " << gameChoices[playerChoice] << endl;
	cout << "Computer Input: " << gameChoices[computerChoice] << endl;
	cout << "--------------------------" << endl << endl;
}

//this function inputs the player and computer choices into the game logic 2d array, 
//which returns a true or false based on whether the player input has won or lost
bool victDecider(int playerChoice, int computerChoice)
{
	gameOutcome = gameLogic[playerChoice][computerChoice];

	return gameOutcome;
}

//this function prints the individual round victor
void roundWin(int playerChoice, int compChoice) {

	//print the round score and current inputs to keep the visuals consistent
	printRoundScore();
	printCurInputs();

	/*
	do a quick intial check to identify a draw state
	if the player input is equal to the computer input:
		display round draw text
		pause the console to allow the user to read the text
		clear the console
	*/
	if (playerChoice == compChoice)
	{
		cout << "[ !!Draw!! ]" << endl << endl;
		system("pause");
		system("CLS");
	}

	//else do the regular checks to decide the victor
	else
	{
		//set the game winner variable equal to the return value of the victDecider function
		gameWinner = victDecider(playerChoice, compChoice);

		string fText = flavorText[playerChoice][compChoice];

		/*
		if the game winner boolean equals true:
			display player round winner text including flavour text
			pause the console to allow the user to read the text
			increment the player score variable by 1
		*/
		if (gameWinner == true)
		{
			cout << "[ " << fText << " ]" << endl << endl;
			cout << "--------------------------" << endl << endl;
			cout << "[ Player Wins!! ]" << endl << endl;
			system("pause");
			playerScore++;
		}
		/*
		if the game winner boolean equals false:
			display computer round winner text including flavour text
			pause the console to allow the user to read the text
			increment the computer score by one
		*/
		else
		{
			cout << "[ " << fText << " ]" << endl << endl;
			cout << "--------------------------" << endl << endl;
			cout << "[ Computer Wins!! ]" << endl << endl;
			system("pause");
			computerScore++;
		}

		//if the round result isnt a draw, increment the current round variable by 1
		curRound++;
	}

	//clear the console
	system("CLS");
}

//this function decides the overall winner
void overallWinner(int compScore, int playerScore) {


	/*in order to prevent an unsatisfying overall draw scenario, decrease the current round
	integer in order to increase the game length until an overall winner is found if the player
	score is the same as the computer score*/
	if (playerScore == compScore)
	{
		curRound--;
	}

	/*if the player score is higher than the computer score
	clear the screen,
	decrement the current round so the round displayed is not higher than the round maximum,
	display computer wins text,
	pause the console to allow the player to read the text,
	call the title menu function*/
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

	/*if the player score is not higher than the computer score
	clear the screen
	decrement the current round so the round displayed is not higher than the round maximum
	display computer wins text
	pause the console to allow the player to read the text
	call the title menu function*/
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

//this function generates a random integer between 0 and 4 (for the computer input) and returns it
int randomNumber() {
	//random_device random;
	//mt19937 ranGen(random());
	//uniform_int_distribution<int> uniq(0, 4);
	//int r_int = uniq(ranGen);

	int r_int = rand() % 4;

	return r_int;
}


//this function prints a help menu for the user containing the numbers corresponding to the moves and the two program actions
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





