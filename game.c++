// Alicia Mullings
// Programming Fundamentals 2 class
// September 1st, 2021
// User can play a game of Tic Tac Toe
// against a smart computer player

#include <iostream>

using namespace std;

// keeps track of player's pieces and turns
enum GAME_PIECES { X_PIECE, O_PIECE, EMPTY_PIECE };

// used to determine game state
enum GAME_STATE { X_WINS, O_WINS, NOT_OVER, TIE };



// keeps track of gamestate
// and gameboard
void playGame(GAME_PIECES player);

// receives and validates human move
void humanMove(int gameBoard[], GAME_PIECES humanPiece);

// determines optimal computer move
void compMove(int gameBoard[], GAME_PIECES humanPiece);

//displays the game board
void displayBoard(int board[]);

// checks game state
GAME_STATE checkState(int gameBoard[], GAME_PIECES player);


int main() {
	// user input to going first
	char answer;

	cout << "Welcome to Tic Tac Toe!\n";
	cout << "-----------------------\n";

	cout << "\nThe person who goes first will be X.\n";
	cout << "The other will be O.\n\n";

	cout << "	| 0 | 1 | 2 | \n";
	cout << "	------------- \n";
	cout << "	| 3 | 4 | 5 | \n";
	cout << "	------------- \n";
	cout << "	| 6 | 7 | 8 | \n";

	cout << "\nMake your move by entering in the number\n";
	cout << "corresponding to an empty space on the board.\n";

	do {
		cout << "\nWould you like to go first (Y/N)? ";
		cin >> answer;
		answer = toupper(answer);

		if (cin.peek() != '\n') {
			cin.clear();
			cin.ignore(100, '\n');

			answer = ' ';
		}

		switch (answer) {
		case 'Y':
			playGame(X_PIECE);
			break;
		case 'N':
			playGame(O_PIECE);
			break;
		default:
			cout << "Invalid entry; looking for Y or N.\n";
		}

	} while (answer != 'Y' && answer != 'N');

	return 0;
}

// keeps track of gamestate
// and gameboard
void playGame(GAME_PIECES player) {
	//game board with pieces, initilized to empty
	int gameBoard[9] = { EMPTY_PIECE, EMPTY_PIECE, EMPTY_PIECE,
						 EMPTY_PIECE, EMPTY_PIECE, EMPTY_PIECE,
						 EMPTY_PIECE, EMPTY_PIECE, EMPTY_PIECE };


	GAME_PIECES humanPiece = player;	// which piece human is
	GAME_STATE curState;				// state game is in

	// if human goes second, set player back
	// to computer
	if (humanPiece == O_PIECE) {
		player = X_PIECE;
	}

	do {

		if (player == humanPiece) {
			humanMove(gameBoard, humanPiece);

			curState = checkState(gameBoard, player);
		}
		else {
			compMove(gameBoard, humanPiece);

			curState = checkState(gameBoard, player);
		}

		if (curState != NOT_OVER && curState != TIE) {
			if (player == humanPiece) {
				cout << "Aw... human wins. :(\n";
			}
			else {
				cout << "Yay! Computer wins! :)\n";
			}
		}

		// switch players
		player = static_cast<GAME_PIECES>(!player);

	} while (curState == NOT_OVER);

}

// receives and validates human move
void humanMove(int gameBoard[], GAME_PIECES humanPiece) {
	int humanMove;		//user input for move

	displayBoard(gameBoard);
	do {
		cout << "\n\nWhere would you like to place your piece? ";
		cin >> humanMove;

		if (humanMove < 0 || humanMove > 8) {
			cout << "Must enter a number between 1 and 8.\n";
		}
		else if (gameBoard[humanMove] != EMPTY_PIECE) {
			cout << "Must choose an empty spot.\n";

			humanMove = 9;
		}

		if (cin.fail() || cin.peek() != '\n') {
			cin.clear();
			cin.ignore(100, '\n');

			cout << "Must enter an integer.";
			humanMove = 9;
		}
	} while (humanMove < 0 || humanMove > 8);

	gameBoard[humanMove] = humanPiece;
}

// determines optimal computer move
void compMove(int gameBoard[], GAME_PIECES humanPiece) {
	// list of moves computer takes
	// if it can't win or block
	const int BEST_MOVES[] = { 4, 0, 2, 6, 8, 1, 3, 5 , 7 };

	int compMove = 10;		// computer's chosen move
	int i = 0;				// counter for while loop

	// check wins
	for (int j = 0; j < 9; j++) {

		if (gameBoard[j] == !humanPiece) {
			// checking horizontal wins
			switch (j % 3) {
				case 0:		// j is at left end
					if (gameBoard[j + 1] == !humanPiece && gameBoard[j + 2] == EMPTY_PIECE) {
						compMove = j + 2;
					}
					if (gameBoard[j + 2] == !humanPiece && gameBoard[j + 1] == EMPTY_PIECE) {
						compMove = j + 1;
					}
					break;
				case 1:		// j is in middle
					if (gameBoard[j + 1] == !humanPiece && gameBoard[j - 1] == EMPTY_PIECE) {
						compMove = j - 1;
					}
					break;
				default:
					break;
			}

			// checking vertical wins
			
		}
	}

	// go down list if can't win/block
	while (compMove == 10) {

		if (gameBoard[BEST_MOVES[i]] == EMPTY_PIECE) {
			compMove = BEST_MOVES[i];
		}

		i++;
	}

	cout << "\nComputer puts piece in position ";
	cout << compMove << ".\n";

	gameBoard[compMove] = !humanPiece;
}

// displays the game board
void displayBoard(int board[]) {
	cout << '\n';
	cout << "	";

	for (int i = 0; i < 9; i++) {
		cout << "| ";

		switch (board[i]) {
		case 0:
			cout << "X";
			break;
		case 1:
			cout << "O";
			break;
		case 2:
			cout << ' ';
			break;
		default:
			cout << "E";	//e for error
		}

		cout << " ";

		if (i % 3 == 2 && i != 8) {
			cout << "|\n";
			cout << "	-------------\n";
			cout << "	";
		}
	}

	cout << "|";
}

// checks and returns game state
GAME_STATE checkState(int gameBoard[], GAME_PIECES player) {
	int emptySpaces = 0;					// counts empty spaces
	GAME_PIECES winner = EMPTY_PIECE;		// stores winner of game

	// counts empty spaces to determine tie
	for (int i = 0; i < 9; i++) {
		if (gameBoard[i] == EMPTY_PIECE) {
			emptySpaces += 1;
		}
	}

	// checks wins based on position 0
	if (gameBoard[0] != EMPTY_PIECE) {
		if (gameBoard[0] == gameBoard[1] && gameBoard[0] == gameBoard[2]) {
			winner = player;
		}
		else if (gameBoard[0] == gameBoard[3] && gameBoard[0] == gameBoard[6]) {
			winner = player;
		}
		else if (gameBoard[0] == gameBoard[4] && gameBoard[0] == gameBoard[8]) {
			winner = player;
		}
	}

	// checks wins based on position 2
	if (gameBoard[2] != EMPTY_PIECE) {
		if (gameBoard[2] == gameBoard[5] && gameBoard[2] == gameBoard[8]) {
			winner = player;
		}
		else if (gameBoard[2] == gameBoard[4] && gameBoard[2] == gameBoard[6]) {
			winner = player;
		}
	}

	// checks wins based on position 1
	if (gameBoard[1] != EMPTY_PIECE) {
		if (gameBoard[1] == gameBoard[4] && gameBoard[1] == gameBoard[7]) {
			winner = player;
		}
	}

	// checks wins based on position 3
	if (gameBoard[3] != EMPTY_PIECE) {
		if (gameBoard[3] == gameBoard[5] && gameBoard[3] == gameBoard[4]) {
			winner = player;
		}
	}

	// checks wins based on position 6
	if (gameBoard[6] != EMPTY_PIECE) {
		if (gameBoard[6] == gameBoard[7] && gameBoard[6] == gameBoard[8]) {
			winner = player;
		}
	}

	// if there is a winner
	if (winner != EMPTY_PIECE) {

		displayBoard(gameBoard);

		cout << "\n";

		switch (winner) {
			case X_PIECE:
				cout << "\n\nX wins. ";
				return X_WINS;
				break;
			case O_PIECE:
				cout << "\n\nO wins. ";
				return O_WINS;
				break;
		}
	} // if no winner, and no empty spaces, TIE
	else if (emptySpaces == 0) {
		cout << "\n\nEnds in a TIE! \n";

		return TIE;
	}

	return NOT_OVER;
}


