#include <curses.h>
#include <unistd.h>
#include "./ai.cpp"

WINDOW *win;

void initBoard(Board &given_board) {
    for(int i = 0; i < 7; ++i) {
        for(int j = 0; j < 6; ++j) {
            given_board.value[i][j] = ' ';
        }
    }
}

void printBoard(Board given_board) {
    //vertical bars
    for(int i = 0; i < 6; ++i) {
        for(int j = 0; j < 8; ++j) {
            move(2*i+1, 4*j);
            addch('|');
        }
    }

    //horizontal bars
    for(int j = 1; j < 7; ++j) {
        for(int i = 0; i < 29; ++i) {
            move(2*j, i);
            addch('-');
        }
    }

    //board pieces
    for(int i = 0; i < 7; ++i) {
        for(int j = 0; j < 6; ++j) {
            mvaddch(1+2*j, 2+4*i, given_board.value[i][j]);
        }
    }
}

//columns are numbered 0->6 (see board def)
bool canDropIntoCol(Board given_board, int col) {
    if(col < 0 || col >= 7) return false;

    int deepest = -1;
    for(int i = 0; i < 6; ++i) {
        if(given_board.value[col][i] == ' ') {
            deepest = i;
        }
    }

    if(deepest < 0) {
        return false;
    }
    else {
        return true;
    }
}

int dropIntoCol(Board &given_board, char player, int col) {
    if(col < 0 || col >= 7) return col;

    int deepest = -1;
    for(int i = 0; i < 6; ++i) {
        if(given_board.value[col][i] == ' ') {
            deepest = i;
        }
    }

    if(deepest < 0) {
        return -1;
    }
    else {
        given_board.value[col][deepest] = player;
    }

    return 0;
}

// return ' ' for no winner or the winning player symbol
char winner(Board given_board) {
    for(int i = 0; i < 7; ++i) {
        for(int j = 0; j < 6; ++j) {
            if(given_board.value[i][j] != ' ') {
                //row
                if(i <= 6-3) {
                    bool success = true;
                    for(int a = i; a-i < 4; ++a) {
                        if(given_board.value[a][j] != given_board.value[i][j]) {
                            success = false;
                        }
                    }
                    if(success) {
                        return given_board.value[i][j];
                    }
                }
                //column
                if(j <= 5-3) {
                    bool success = true;
                    for(int a = j; a-j < 4; ++a) {
                        if(given_board.value[i][a] != given_board.value[i][j]) {
                            success = false;
                        }
                    }
                    if(success) {
                        return given_board.value[i][j];
                    }
                }
                //diagonal (down-right)
                if(i <= 6-3 && j <= 5-3) {
                    bool success = true;
                    for(int a = i, b = j; a-i < 4 && b-j < 4; ++a, ++b) {
                        if(given_board.value[a][b] != given_board.value[i][j]) {
                            success = false;
                        }
                    }
                    if(success) {
                        return given_board.value[i][j];
                    }
                }
                //diagonal (down-left)
                if(i >= 3 && j <= 5-3) {
                    bool success = true;
                    for(int a = i, b = j; i-a < 4 && b-j < 4; --a, ++b) {
                        if(given_board.value[a][b] != given_board.value[i][j]) {
                            success = false;
                        }
                    }
                    if(success) {
                        return given_board.value[i][j];
                    }
                }
            }
        }
    }

    return ' ';
}

void runGame(char who_is_ai, int x_ai_level=0, int o_ai_level=0) {
    char whose_turn = 'X'; //X turn first
    int ch;
    int xpos = 2;

    clear();

    Board given_board = Board();
    initBoard(given_board);

    while(true) {
        //make sure it's not the AI's turn
        if(whose_turn == who_is_ai || who_is_ai == 'b') {
            move(14, 0);
            printw("Thinking...");
            refresh();

            int status = makeMinimaxMoveAI(given_board, whose_turn, (whose_turn=='X')?x_ai_level:o_ai_level);

            if(status == 0) {
                whose_turn = (whose_turn == 'X')?'O':'X';
            }
 
            usleep(1000000); //so the user can see what's going on.           
            clear();
        }
        //since it's not the AI's turn, we accept user input
        else {
            ch = getch();
            switch(ch) {
                case KEY_LEFT:
                    if(xpos > 2) {
                        xpos -= 4;
                    }
                    clear();
                break;
                case KEY_RIGHT:
                    if(xpos < 25) {
                        xpos += 4;
                    }
                    clear();
                break;
                case ' ':
                    int res = dropIntoCol(given_board, whose_turn, (xpos-2)/4);
                    if(res == 0) {
                        whose_turn = (whose_turn == 'X')?'O':'X';
                    }
                    clear();
                break;
            }
        }

        //output stuff
        char victory = winner(given_board);
        if(victory != ' ') {
            while(true) {
                ch = getch();
                switch(ch) {
                    case ' ':
                        return;
                    break;
                }

                printBoard(given_board);
                move(15, 0);
                printw("Congratulations Player ");
                addch(victory);
            
                move(16, 0);
                printw("Press SPACE to exit...");
    
                refresh();
            }
        }
        else {
            //print board and piece
            printBoard(given_board);
            mvaddch(0, xpos, whose_turn);

            refresh();
        }
    }
}
