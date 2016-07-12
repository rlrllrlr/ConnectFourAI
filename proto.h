struct Board {
    char value[7][6];
};

void init(void);
void runGame(Board &given_board);

void initBoard(Board &given_board);
void printBoard(Board given_board);

bool canDropIntoCol(Board given_board, int col);
int dropIntoCol(Board &given_board, char player, int col);

char winner(Board given_board);
