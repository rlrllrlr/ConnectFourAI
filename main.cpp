#include <iostream>
#include <cstdlib>
#include <curses.h>
#include <unistd.h>
#include "./proto.h"
#include "./ai.cpp"
using namespace std;

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
            wmove(win, 2*i+1, 4*j);
            waddch(win, '|');
        }
    }

    //horizontal bars
    for(int j = 1; j < 7; ++j) {
        for(int i = 0; i < 29; ++i) {
            wmove(win, 2*j, i);
            waddch(win, '-');
        }
    }

    //board pieces
    for(int i = 0; i < 7; ++i) {
        for(int j = 0; j < 6; ++j) {
            mvwaddch(win, 1+2*j, 2+4*i, given_board.value[i][j]);
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
                if(i <= 6-4) {
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
                if(j <= 7-4) {
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
                if(i <= 6-4 && j <= 7-4) {
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
                if(i >= 3 && j <= 7-4) {
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

void init(void) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    curs_set(0);

    int h, w;
    getmaxyx(stdscr, h, w);
    win = newwin(h, w, 0, 0);
    
    nodelay(stdscr, TRUE);
}

void runGame(Board &given_board, char who_is_ai) {
    char whose_turn = 'X'; //X turn first
    int ch;
    int xpos = 2;

    while(true) {
        //make sure it's not the AI's turn
        if(whose_turn == who_is_ai || who_is_ai == 'b') {
            int status = makeMinimaxMoveAI(given_board, whose_turn);

            if(status == 0) {
                whose_turn = (whose_turn == 'X')?'O':'X';
            }
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
                wmove(win, 15, 0);
                wprintw(win, "Congratulations Player ");
                waddch(win, victory);
            
                wmove(win, 16, 0);
                wprintw(win, "Press space to exit...");
    
                wrefresh(win);
            }
        }
        else {
            printBoard(given_board);
            mvwaddch(win, 0, xpos, whose_turn);
            wrefresh(win);
        }
    }
}

int main(void) {
    char who_is_ai = 'O'; //symbol of AI player. ' ' if no AI and 'b' if both AI.
    Board main_board;

    init();

    initBoard(main_board);
    runGame(main_board, who_is_ai);

    endwin();
    return 0;
}
