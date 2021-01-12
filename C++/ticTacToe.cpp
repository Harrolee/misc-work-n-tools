#include <iostream>
#include <vector>
#include <string>
using namespace std;

//write tic tac toe
/*
 - two players at keyboard
	- x
	- o
 - Win conditions:
	- three adjacent marks

Things I need:
Questions:
	presentation: how do users see the board
	input: how do users indicate which location they want to put an x on
	logic: 
		- is the user's move legal?
		- is the game over?
			- Did someone win?
				- Who?

Answers:
	pres:
		At each turn:
			[X]1. print a chart of the board.
					2 > _|_|_
					1 > _|_|_
					0 > _|_|_
						^ ^ ^
						0 1 2
			[X]2. state whose turn it is.
			[X]3. ask for a move in # # format
	input:
		[X] recieve: # # 
	logic:
		main loop: while game == true
			[X]1. print turn content
			[X]2. recieve move input
			[X]3. apply input to internal array
			[X]4. check internal array for win conditions
			[X]5. if game!=over, return to step 1. if game==over, display board and declare the winner

		save and evaluate state: use 3x3 int array
*/
//char board1[13]{ '2',' ','>',' ','_',' ','|',' ','_',' ','|',' ','_' };
//char board2[13]{ '1',' ','>',' ','_',' ','|',' ','_',' ','|',' ','_' };
//char board3[13]{ '0',' ','>',' ','_',' ','|',' ','_',' ','|',' ','_' };
//char board4[13]{ ' ',' ',' ',' ','^',' ',' ',' ','^',' ',' ',' ','^' };
//char board5[13]{ ' ',' ',' ',' ','0',' ',' ',' ','1',' ',' ',' ','2' };


char gameBoard[3][3] = {};
char playerBoard[5][14] {
	{'0',' ','>',' ','_',' ','|',' ','_',' ','|',' ','_','\0'},
	{'1',' ','>',' ','_',' ','|',' ','_',' ','|',' ','_','\0'},
	{'2',' ','>',' ','_',' ','|',' ','_',' ','|',' ','_','\0'},
	{' ',' ',' ',' ','^',' ',' ',' ','^',' ',' ',' ','^','\0'},
	{' ',' ',' ',' ','0',' ',' ',' ','1',' ',' ',' ','2','\0'}
};

void printTurn(char currPlayer) {
	for (int i = 0; i < 5; i++) {
		cout << playerBoard[i] << "\n";
	}
	cout << currPlayer << ", it is your turn.\n";
}

bool checkWin() {
	char player;
	bool gameOver = false;
	// check center
	if (gameBoard[1][1]) {
		player = gameBoard[1][1];
		// check middle row
		if (gameBoard[1][0] == player && gameBoard[1][2] == player) {
			gameOver = true;
		}
		// check middle column
		else if (gameBoard[0][1] == player && gameBoard[2][1] == player) {
			gameOver = true;
		}// check L diagonal
		else if (gameBoard[0][0] == player && gameBoard[2][2] == player) {
			gameOver = true;
		}// check R diagonal
		else if (gameBoard[0][2] == player && gameBoard[2][0] == player) {
			gameOver = true;
		}
	}
	if (gameBoard[0][0]) {
		player = gameBoard[0][0];
		// top row
		if (gameBoard[0][1] == player && gameBoard[0][2] == player) {
			gameOver = true;
		} // left column
		else if (gameBoard[1][0] == player && gameBoard[2][0] == player) {
			gameOver = true;
		}
	}
	if (gameBoard[2][2]) {
		player = gameBoard[2][2];
		// bot row
		if (gameBoard[2][0] == player && gameBoard[2][1] == player) {
			gameOver = true;
		} // right col
		else if (gameBoard[0][2] == player && gameBoard[1][2] == player) {
			gameOver = true;
		}
	}
	return gameOver;
}
	/*
	* We have the game board.
	* Check the middle. if there, pass value at middle into var.
	*	if there:
	*		check middle row
	*		check middle column
	*		check diagonals
	*	if not:
	*		check top left corner.
	*			if there:
	*				check left col
	*				check top row
	*			if not:
	*				check bottom right corner
	*					check bottom row
	*					check right col
	* starting at [0][0], see if 
	win conditions:
	
	*/
int requestInput() {
	int turn;
	//vector<int> valid_input = { 0,1,2 };
	//get row
	cin >> turn;
	while (!(turn == 0 || turn == 1 || turn == 2)) {
		cout << "Please select a valid number\n";
		cin >> turn;
	}
	return turn;
}

vector<int> userInput(char currPlayer) {
	vector<int> turn(2);
	bool takingInput = true;

	// Request, receive, and validate input:
	while (takingInput) {
		// help the user to submit valid input:
		cout << "Row 0-2?\n";
		turn[0] = requestInput();
		cout << "Column 0-2?\n";
		turn[1] = requestInput();

		// Validate that the input is not already present on int array gameBoard with an if statement.
		// If it is not present, we can stop taking input.
		if (gameBoard[turn[0]][turn[1]] == 'X' || gameBoard[turn[0]][turn[1]] == 'O') {
			cout << "Someone has already moved there. Please select a different location.\n";
		}
		else {
			takingInput = false;
		}
	}
	return turn;
}

void updateBoards(vector<int> turn, char currPlayer) {
	gameBoard[turn[0]][turn[1]] = currPlayer;
	playerBoard[turn[0]][(turn[1] + 1) * 4] = currPlayer;
}

char switchPlayer(char currPlayer) {
	if (currPlayer == 'X') {
		currPlayer = 'O';
	}
	else {
		currPlayer = 'X';
	}
	return currPlayer;
}

int main() {
	int turnCount = 0;
	bool gameOver = false;
	char currPlayer = 'X';

	if (gameBoard[1][1]) {
		cout << "test?";
	}
	else {
		cout << "absent??";
	}

	// game loop:
	while(gameOver==false){
		printTurn(currPlayer);

		// request user input and then apply it to the gameBoard and playerBoard:
		updateBoards(userInput(currPlayer), currPlayer);

		// increment turnCount
		turnCount++;

		if (turnCount > 4) {
			switch (checkWin())
			{
			case true:
				cout << "Congrats " << currPlayer << ", you won!\n";
				gameOver = true;
			default:
				// check for cat's game
				// When turnCount is 9 and someone hasn't won, it's a tie.
				if (turnCount == 9) {
					cout << "Alas, 'twas a cat's game.\n";
					gameOver = true;
				}
			}
		}
		currPlayer = switchPlayer(currPlayer);
	}
}

