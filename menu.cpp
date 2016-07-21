#include <curses.h>
#include "run_game.cpp"

void PvCMenu() {
    clear();

    int option = 0;   
    int selection1 = 1;
    int selection2 = 0;

    while(true) {
        // output stuff
        attron(A_BOLD | A_UNDERLINE);
        move(0, 0);
        printw("Player v Computer Menu");
        attroff(A_BOLD | A_UNDERLINE);

        move(2, 0);
        printw("Difficulty: ");

        for(int i = 1; i <= 4; ++i) {
            if(selection1 == i && option == 0) {
                attron(A_REVERSE);
            }
            else if(selection1 == i && option == 1) {
                attron(A_DIM | A_UNDERLINE);
            }
            addch((char)(48+i));
            attroff(A_REVERSE | A_DIM | A_UNDERLINE);

            addch(' ');
        }

        move(4, 0);
        printw("Computer (X goes first): ");

        if(selection2 == 0 && option == 1) {
            attron(A_REVERSE);
        }
        else if(selection2 == 0 && option == 0) {
            attron(A_DIM | A_UNDERLINE);
        }
        printw("X");
        attroff(A_DIM | A_UNDERLINE | A_REVERSE);

        printw(" ");

        if(selection2 == 1 && option == 1) {
            attron(A_REVERSE);
        }
        else if(selection2 == 1 && option == 0) {
            attron(A_DIM | A_UNDERLINE);
        }
        printw("O");
        attroff(A_DIM | A_UNDERLINE | A_REVERSE);

        move(6, 0);
        attron(A_BOLD);
        printw("Use the arrow keys to set AI difficulty and symbol.");
        move(7, 0);
        printw("Press SPACE to start.");
        attroff(A_BOLD);

        refresh();

        //input stuff
        int ch = getch();
        switch(ch) {
            case KEY_RIGHT:
                if(option == 0) {
                    if(selection1 < 4) {
                        selection1 += 1;
                    }
                }
                else if(option == 1) {
                    if(selection2 < 1) {
                        selection2 += 1;
                    }
                }
            break;
            case KEY_LEFT:
                if(option == 0) {
                    if(selection1 > 1) {
                        selection1 -= 1;
                    }
                }
                else if(option == 1) {
                    if(selection2 > 0) {
                        selection2 -= 1;
                    }
                }
            break;
            case KEY_DOWN:
                if(option < 1) {
                    option += 1;
                }
            break;
            case KEY_UP:
                if(option > 0) {
                    option -= 1;
                }
            break;
            case ' ':
                if(selection2 == 0) {
                    runGame('X', selection1*2, 0);
                }
                else if(selection2 == 1) {
                    runGame('O', 0, selection1*2);
                }
                return;
            break;
        }
    }
}

void CvCMenu() {
    clear();

    int selection1 = 1,
        selection2 = 1,
        option = 0;

    while(true) {
        //output stuff

        attron(A_UNDERLINE | A_BOLD);
        move(0, 0);
        printw("Computer v Computer Menu");
        attroff(A_UNDERLINE | A_BOLD);

        move(2, 0);
        printw("X Difficulty: ");
        for(int i = 1; i <= 4; ++i) {
            if(selection1 == i) {
                if(option == 0) {
                    attron(A_REVERSE);
                }
                else if(option == 1) {
                    attron(A_DIM | A_UNDERLINE);
                }
            }
            addch((48+i));
            attroff(A_DIM | A_UNDERLINE | A_REVERSE);

            addch(' ');
        }

        move(4, 0);
        printw("O Difficulty: ");
        for(int i = 1; i <= 4; ++i) {
            if(selection2 == i) {
                if(option == 1) {
                    attron(A_REVERSE);
                }
                else if(option == 0) {
                    attron(A_DIM | A_UNDERLINE);
                }
            }
            addch((48+i));
            attroff(A_DIM | A_UNDERLINE | A_REVERSE);

            addch(' ');
        }

        attron(A_BOLD);
        move(6, 0);
        printw("Use the arrow keys to set each AI's difficulty.");
        move(7, 0);
        printw("Press SPACE to start.");
        attroff(A_BOLD);

        refresh();

        //input stuff
        
        int ch = getch();
        switch(ch) {
            case KEY_LEFT:
                if(option == 0) {
                    if(selection1 > 1) {
                        selection1 -= 1;
                    }
                }
                else if(option == 1) {
                    if(selection2 > 1) {
                        selection2 -= 1;
                    }
                }
            break;
            case KEY_RIGHT:
                if(option == 0) {
                    if(selection1 < 4) {
                        selection1 += 1;
                    }
                }
                else if(option == 1) {
                    if(selection2 < 4) {
                        selection2 += 1;
                    }
                }
            break;
            case KEY_UP:
                if(option > 0) {
                    option -= 1;
                }
            break;
            case KEY_DOWN:
                if(option < 1) {
                    option += 1;
                }
            break;
            case ' ':
                runGame('b', selection1*2, selection2*2);
                return;
            break;
        }
    }
}

void mainMenu() {
    int selection = 0;
    while(true) {
        /* output stuff */
        //title
        attron(A_UNDERLINE | A_BOLD);
        move(0, 0);
        printw("Main Menu");
        attroff(A_UNDERLINE | A_BOLD);

        if(selection == 0) {
            attron(A_REVERSE);
        }
        move(2, 0);
        printw("Player v Player");
        attroff(A_REVERSE);

        if(selection == 1) {
            attron(A_REVERSE);
        }
        move(4, 0);
        printw("Player v Computer");
        attroff(A_REVERSE);

        if(selection == 2) {
            attron(A_REVERSE);
        }
        move(6, 0);
        printw("Computer v Computer");
        attroff(A_REVERSE);

        attron(A_BOLD);
        move(8, 0);
        printw("Use the arrow keys to select a game type.");
        move(9, 0);
        printw("Press SPACE to continue.");
        attroff(A_BOLD);

        refresh();

        /* input stuff */
        int ch = getch();
        switch(ch) {
            case KEY_DOWN:
                if(selection < 2) {
                    selection += 1;
                }
            break;
            case KEY_UP:
                if(selection > 0) {
                    selection -= 1;
                }
            break;
            case ' ':
                if(selection == 0) {
                    runGame(' ');
                }
                if(selection == 1) {
                    PvCMenu();
                }
                if(selection == 2) {
                    CvCMenu();
                }

                return;
            break;
        }
    }
}

void init(void) {
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, true);
    curs_set(0);

    nodelay(stdscr, TRUE);
}

int main(void) {
    init();
    mainMenu();
    endwin();
    return 0;
}
