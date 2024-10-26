// user - tanavposwal939
#include <bits/stdc++.h>
using namespace std;

// white - small
// black - capital

char board[8][8] = {
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
    };

void board_cout(char board[8][8]) {
	cout << "+-----------------+" << endl;
	for (int i = 0; i < 8; i++) {
		// border
		cout << "| ";

		for (int j = 0; j < 8; j++) {
			if (board[i][j] != '.') {
				cout << board[i][j] << " ";
			} else {
				cout << "  ";
			}
		}

		cout << "|" << endl;
	}
	cout << "+-----------------+" << endl;
}

void move_piece(string from, string to) {
    // convert to array indexs
    // no move validation yet
}

int main() {
	board_cout(board);

	// move pawn

	return 0;
}