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

map<char, vector<pair<int, int>>> rules = {
    // Pawn (handled separately, since direction depends on color)
    {'p', {{1, 0}, {1, 1}, {1, -1}}},    // black pawn moves down (+1 row)
    {'P', {{-1, 0}, {-1, 1}, {-1, -1}}}, // white pawn moves up (-1 row)

    // Knight (L-shape)
    {'n', {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}}},
    {'N', {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}}},

    // Bishop (diagonals)
    {'b', {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}}},
    {'B', {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}}},

    // Rook (straight lines)
    {'r', {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}},
    {'R', {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}},

    // Queen (rook + bishop combined)
    {'q', {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}}},
    {'Q', {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}}},

    // King (one step in any direction)
    {'k', {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}}},
    {'K', {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}}},
};

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

pair<int, int> findCoord(string notation)
{
    int row = notation[0] - 'a';
    int col = '8' - notation[1];

    return {col, row};
}

string makeNotation(pair<int, int> coord)
{
    string notation = "";

    notation += coord.first + 'a';
    notation += '8' + coord.second;

    return notation;
}

bool isValidMove(string from, string to, char board[8][8])
{
    pair<int, int> fromCoord = findCoord(from);
    pair<int, int> toCoord = findCoord(to);

    int fromRow = fromCoord.first;
    int fromCol = fromCoord.second;
    int toRow = toCoord.first;
    int toCol = toCoord.second;

    // get the piece
    char piece = board[fromRow][fromCol];
    char dest = board[toRow][toCol];

    if (piece == ' ')
        return false;

    int dx = toRow - fromRow;
    int dy = toCol - fromCol;

    // Normalize direction for sliding pieces
    int sdx = (dx == 0 ? 0 : dx / abs(dx));
    int sdy = (dy == 0 ? 0 : dy / abs(dy));

    // Pawn special case
    if (tolower(piece) == 'p')
    {
        bool isWhite = isupper(piece);
        int dir = isWhite ? -1 : 1;

        // Move forward
        if (dy == 0 && dest == ' ' && dx == dir)
            return true;

        // Double move
        if (dy == 0 && dest == ' ' &&
            ((isWhite && fromRow == 6 && dx == -2) ||
             (!isWhite && fromRow == 1 && dx == 2)))
            return true;

        // Capture diagonally
        if (abs(dy) == 1 && dx == dir && dest != ' ')
            return true;

        return false;
    }

    // Knight, King: single-step moves
    if (tolower(piece) == 'n' || tolower(piece) == 'k')
    {
        for (auto m : rules[piece])
        {
            if (dx == m.first && dy == m.second)
                return true;
        }
        return false;
    }

    // Sliding pieces (bishop, rook, queen)
    if (tolower(piece) == 'b' || tolower(piece) == 'r' || tolower(piece) == 'q')
    {
        bool validDir = false;
        for (auto m : rules[piece])
        {
            if (sdx == m.first && sdy == m.second)
            {
                validDir = true;
                break;
            }
        }
        if (!validDir)
            return false;

        // Check path is clear
        int r = fromRow + sdx;
        int c = fromCol + sdy;
        while (r != toRow || c != toCol)
        {
            if (board[r][c] != ' ')
                return false;
            r += sdx;
            c += sdy;
        }
        return true;
    }

    return false;
}

bool move_piece(string from, string to, char board[8][8])
{
    // if (!isValidMove(from, to, board))
    // {
    //     cout << "^ Invalid move: " << from << to << endl;
    //     return false;
    // }

    pair<int, int> f = findCoord(from);
    pair<int, int> t = findCoord(to);
    if (board[f.first][f.second] != '.')
    {
        board[t.first][t.second] = board[f.first][f.second];
        board[f.first][f.second] = '.';
    }
    return true;
}

bool humanTurn(bool &run)
{
    cout << "---- YOURs TURN (ex: a2a4, q to quit) ----" << endl;

    string in;
    string from;
    string to;
    cout << ">> ";
    cin >> in; // a2a4

    if (in == "q")
    {
        run = false;
        return false;
    }

    from = in.substr(0, 2);
    to = in.substr(2, 2);

    if (!move_piece(from, to, board))
        return false;

    return true;
}

bool robotTurn(bool &run)
{
    cout << "## Robot pseudo moved pieces" << endl;
    return true;
}

int main()
{

    bool run = true;

    while (run)
    {
        board_cout(board);

        if (humanTurn(run))
            robotTurn(run);

        if (run == false)
            break;
    }

    return 0;
}