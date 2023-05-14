#include <string>
#include <iostream>
#include <vector>

using namespace std;

namespace Games
{

#pragma region Quiz
	int Quiz() {
		cout << "We are playing quiz\n";

		const int q_amount = 3;
		string questions[q_amount] = {
			"Name the capital of the UK",
			"Name the second planet from the Sun",
			"Name the year of USSR collapse"
		};
		string answers[q_amount] = {
			"London",
			"Venus",
			"1991"
		};
		string current_answer;

		int score = 0;
		for (int i = 0; i < q_amount; i++) {
			cout << questions[i] << endl;
			cin >> current_answer;
			if (current_answer == answers[i]) {		// Answers and questions are connected through the identical index
				// If current answer is correct, notify and increase the score
				cout << "Correct\n";
				score++;
			}
			else
				cout << "Incorrect\n";

		}
		cout << "=========================\n";
		char buffer[255];																	// Buffer to store formatted text in
		int res = snprintf(buffer, 255, "Your score is %d/%d", score, q_amount);			// Format the text and store inside the buffer
		string verdict = (score < q_amount / 2 + 1) ? " - you suck" : " - you are good";	// Fabricate verdict according to acquired score (mediocre score is a bound)
		cout << buffer << verdict << endl;
		return 0;
	}
#pragma endregion

#pragma region TicTacToe

	/**
	*	Simply checks every possible condition of win.
	*
	*	@param board - current board
	*	@param player - current player's symbol
	*	@return True if player won and false if player has not won
	*/
	bool isWon(char board[][3], char player) {
		
		if (board[0][0] == player && board[0][1] == player && board[0][2] == player) return 1;
		if (board[1][0] == player && board[1][1] == player && board[1][2] == player) return 1;
		if (board[2][0] == player && board[2][1] == player && board[2][2] == player) return 1;

		if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return 1;
		if (board[2][0] == player && board[1][1] == player && board[0][2] == player) return 1;

		if (board[0][0] == player && board[1][0] == player && board[2][0] == player) return 1;
		if (board[0][1] == player && board[1][1] == player && board[2][1] == player) return 1;
		if (board[0][2] == player && board[1][2] == player && board[2][2] == player) return 1;
		return 0;
	}

	/**
	*	Checks if no player has won and if there are empty cells left.
	*
	*	@param board - current board
	*	@return True if this is draw and false otherwise
	*/
	bool isDraw(char board[3][3]) {
		if (isWon(board, 'X') || isWon(board, 'O')) return 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board[i][j] == ' ') {
					return 0;
				}
			}
		}
		return 1;
	}

	/**
	*	Replaces empty cell with player's symbol.
	*
	*	@param board - current board
	*	@param player - current player's symbol
	*	@param posX - X coordinate of player's move
	*	@param posY - Y coordinate of player's move
	*/
	void makeMove(char board[3][3], char player, unsigned short int posX, unsigned short int posY) {
		board[posX][posY] = player;
	}

	/**
	*	Checks if provided cell is empty.
	*
	*	@param board - current board.
	*	@param x - X coordinate of the cell to check.
	*	@param y - Y coordinate of the cell to check.
	*	@return True if the cell is empty and false otherwise.
	*/
	bool isEmpty(char board[3][3], unsigned short int x, unsigned short int y) {
		if (board[x][y] == ' ') return 1;
		return 0;
	}

	/**
	*	Primitive AI algorithms that randomly searches for valid move.
	*
	*	@param board - current board.
	*	@param bot - current bot's symbol.
	*/
	void botMove(char board[3][3], char bot) {
		unsigned short int x, y;
		do {
			x = rand() / ((RAND_MAX + 1u) / 3);		// Pseudo-random number in the range from 0 to 2 (inclusive)
			y = rand() / ((RAND_MAX + 1u) / 3);		// Pseudo-random number in the range from 0 to 2 (inclusive)
		} while (!isEmpty(board, x, y));
		board[x][y] = bot;
	}

	/**
	*	Renders current board in a fancy way.
	*
	*	@param board - current board.
	*/
	void displayBoard(char board[3][3]) {
		cout << "\n_______\n";
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << '|' << board[i][j];
			}
			cout << "|\n-------\n";
		}
	}

	int TicTacToe() {
		cout << "We are playing Tic-Tac-Toe\nPick a side (X/O)\n";

		char player;
		cin >> player;

		char board[3][3] = {
			{' ', ' ', ' '},
			{' ', ' ', ' '},
			{' ', ' ', ' '}
		};

		char turn = 'X';
		unsigned short int moveX, moveY;

		while (!isWon(board, 'X') && !isWon(board, 'O') && !isDraw(board)) {
			displayBoard(board);
			cout << "Current player is " << turn << endl;
			if (turn == player) {
				// If it is player's turn
				cout << "Input your coordinations: ";
				cin >> moveX >> moveY;
				makeMove(board, player, moveX, moveY);
			}
			else {
				// If it is bot's turn
				cout << "Bot is making the move";
				botMove(board, turn);
			}
			cout << '\n';
			turn = (turn == 'O') ? 'X' : 'O';		// Swap players
		}
		cout << "=======================\n";
		displayBoard(board);
		if (isDraw(board)) cout << "This is draw\n";
		if (isWon(board, player)) cout << "Congrats! You won!\n";
		else cout << "You suck! Even random moving bot defeated you!\n";
		return 0;
	}
#pragma endregion

}