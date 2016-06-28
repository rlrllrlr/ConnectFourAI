#include <iostream>
#include <curses.h>
#include <unistd.h>
using namespace std;

char board[7][6];
WINDOW *win;

void initBoard(void) {
    for(int i = 0; i < 7; ++i) {
        for(int j = 0; j < 6; ++j) {
            board[i][j] = ' ';
        }
    }
}

void printBoard(void) {
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
            mvwaddch(win, 1+2*j, 2+4*i, board[i][j]);
        }
    }
}

//columns are numbered 0->5 (see board def)
int dropIntoCol(char player, int col) {
    if(col < 0 || col >= 6) return col;

    int deepest = -1;
    for(int i = 0; i < 6; ++i) {
        if(board[col][i] == ' ') {
            deepest = i;
        }
    }

    if(deepest < 0) {
        return -1;
    }
    else {
        board[col][deepest] = player;
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

void runGame(void) {
    char whose_turn = 'X'; //X turn first
 
    int xpos = 2;
    while(true) {
        //input stuff
        int ch = getch();
        switch(ch) {
            case KEY_LEFT:
                if(xpos > 2) {
                    xpos -= 4;
                }
            break;
            case KEY_RIGHT:
                if(xpos < 25) {
                    xpos += 4;
                }
            break;
            case ' ':
                int res = dropIntoCol(whose_turn, (xpos-2)/4);
                if(res == 0) {
                    whose_turn = (whose_turn == 'X')?'O':'X';
                }
            break;
        }

        //output stuff
        clear();
        printBoard();
        mvwaddch(win, 0, xpos, whose_turn);
        wrefresh(win);

        //wait a bit
        usleep(10000);
    }
}

int main(void) {
    init();
    initBoard();
    runGame();
    return 0;
}
