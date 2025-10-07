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
    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}};

void board_cout(char board[8][8])
{
    cout << endl
         << " +-----------------+" << endl;
    for (int i = 0; i < 8; i++)
    {
        // border
        cout << (8 - i);
        cout << "| ";

        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] != '.')
            {
                cout << board[i][j] << " ";
            }
            else
            {
                cout << "  ";
            }
        }

        cout << "|" << endl;
    }
    cout << " +-----------------+" << endl;
    cout << "   a b c d e f g h" << endl
         << endl;
}

pair<int, int> findCoord(string point)
{
    int col = '8' - point[1];
    int row = point[0] - 'a';

    return {col, row};
}

void move_piece(string from, string to)
{
    // TODO: validate move
    pair<int, int> f = findCoord(from);
    pair<int, int> t = findCoord(to);
    if (board[f.first][f.second] != '.')
    {
        board[t.first][t.second] = board[f.first][f.second];
        board[f.first][f.second] = '.';
    }
}

int main()
{

    bool run = true;

    while (run)
    {
        board_cout(board);

        cout << "---- YOURs TURN (q q to quit) ----" << endl;

        string from;
        string to;
        cout << ">> ";
        cin >> from >> to;

        if (from == "q" && to == "q")
        {
            run = false;
            break;
        }

        move_piece(from, to);
    }

    return 0;
}