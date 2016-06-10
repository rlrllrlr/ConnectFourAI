#include <iostream>
using namespace std;

char board[7][6];

void initBoard(void) {
	for(int i = 0; i < 7; ++i) {
		for(int j = 0; j < 6; ++j) {
			board[i][j] = 'X';
		}
	}
}

void printBoard(void) {
	for(int i = 0; i < 7; ++i) {
		for(int j = 0; j < 6; ++j) {
			cout << board[i][j];
		}
		cout << endl;
	}
}

//columns are numbered 0->5 (see board def)
int dropIntoCol(char player, int col) {
	if(col < 0 || col > 5) return -1;

	int deepest = -1;
	for(int i = 0; i < 7; ++i) {
		if(board[i][col] == 'X') {
			deepest = i;
		}
	}

	if(deepest < 0) {
		return -1;
	}
	else {
		board[deepest][col] = player;
	}

	return 0;
}

// return 'X' for no winner or the winning player symbol
char winner(void) {
	for(int i = 0; i < 7; ++i) {
		for(int j = 0; j < 6; ++j) {
			if(board[i][j] != 'X') {
				//column
				if(i < 6-4) {
				}
				//row
				if(j < 7-4) {
				}
				//diagonal
				if(i < 6-4 && j < 7-4) {
				}
			}
		}
	}
}

int main(void) {
	initBoard();
	printBoard();
	dropIntoCol('R', 2);
	dropIntoCol('B', 2);
	cout << endl;
	printBoard();

	return 0;
}
