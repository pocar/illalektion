#include <cstdio>
#include <cstring>

enum Move_e {
    CIRCLE,
    CROSS
};

struct TicTacToe {
    char board[9];  // { a1, a2, a3, b1, b2, b3, c1, c2, c3 }
    Move_e player;

    constexpr static unsigned maxIndex = sizeof(board)/sizeof(board[0]);

    TicTacToe();
    void printBoard() const;
    bool place(char row, char column);

    bool threeInRow(char row, char column) const;
    bool isDraw() const;

    unsigned getField(char row, char col) const;
    inline char getLastMovePlayer() const
    {
        if (CIRCLE == player) {
            return 'x';
        } else {
            return 'o';
        }
    }
};


TicTacToe::TicTacToe()
{
    for(size_t i = 0; i < maxIndex; ++i) {
        board[i] = ' ';
    }
    player = CIRCLE;
}

unsigned TicTacToe::getField(char row, char col) const
{
    size_t i = row * 3 + col;

    if (i >= maxIndex) return maxIndex;
    return i;
}

void TicTacToe::printBoard() const
{
    printf("   1 2 3 \n       \n");
    for(unsigned int i = 0; i < 3; ++i) {
        printf("%c ", 'a'+i);
        for (unsigned int j = 0; j < 3; ++j)
            printf(" %c", board[i*3 + j]);
        printf("\n");
    }
}

bool TicTacToe::place(char row, char column)
{
    unsigned i = getField(row, column);
    if (maxIndex == i) {
            printf("Invalid coordinate!\n");
            return false;
    }

    switch(board[i]) {
        case ' ':
            if (CIRCLE == player) {
                board[i] = 'o';
                player = CROSS;
            } else {
                board[i] = 'x';
                player = CIRCLE;
            }
            return true;
        default:
            printf("Invalid move!\n");
            return false;
    }
}

bool TicTacToe::threeInRow(char row, char column) const
{
    char sym = board[getField(row, column)];

    // three in row
    unsigned count = 0;
    for (unsigned i = 0; i < 3; ++i) {
        if (board[getField(row, i)] == sym) {
            ++count;
        }
    }
    if (3 == count) return true;

    // three in column
    count = 0;
    for (unsigned i = 0; i < 3; ++i) {
        if (board[getField(i, column)] == sym) {
            ++count;
        }
    }
    if (3 == count) return true;

    // diagonal top-left -> bottom-right
    count = 0;
    for (unsigned i = 0; i < 3; ++i) {
        if (board[getField(i, i)] == sym) {
            ++count;
        }
    }
    if (3 == count) return true;

    // diagonal bottom-right -> top-left
    count = 0;
    for (unsigned i = 0; i < 3; ++i) {
        if (board[getField(i, 3-i)] == sym) {
            ++count;
        }
    }
    if (3 == count) return true;

    return false;
}

bool TicTacToe::isDraw() const
{
    for(unsigned i = 0; i < maxIndex; ++i) {
        if (' ' == board[i]) {
            return false;
        }
    }
    return true;
}


int main()
{
    char row, column;
    TicTacToe game;

    bool isValid;

    do {
        game.printBoard();
        printf("\nIn what field to place: ");
        char line[100];
        fgets(line, sizeof(line)/sizeof(line[0]), stdin);

        if (false == game.place(line[0]-'a', line[1]-'1'))
            continue;

        if (true == game.threeInRow(line[0]-'a', line[1]-'1')) {
            printf("Player '%c' won!\n", game.getLastMovePlayer());
            return 0;
        }

    } while(false == game.isDraw());

    printf("Game ended in draw!\n");

    return 0;
}
