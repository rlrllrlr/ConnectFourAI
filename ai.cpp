#include <iostream>
#include <unistd.h>
#include <cmath>
using namespace std;

#define STEPS_AHEAD 8

// + ratings are good for player and - ratings are good for opponent
int rateBoard(Board given_board, char player) {
    char opp = (player == 'X')?'O':'X';

    int score = 0;

    //check rows
    for(int row = 0; row < 6; ++row) {
        for(int col = 0; col < 4; ++col) {

            int player_counter = 0, opp_counter = 0;
            for(int a = 0; a < 4; ++a) {
                if(given_board.value[col+a][row] == player) {
                    player_counter += 1;
                }
                if(given_board.value[col+a][row] == opp) {
                    opp_counter += 1;
                }
            }

            //neither player can win a group occupied by both
            if(player_counter > 0 && opp_counter > 0) {
                continue;
            }
            else if(player_counter > 0) {
                if(player_counter >= 4) {
                    return 8000000;
                }

                score += 10*player_counter;
            }
            else if(opp_counter > 0) {
                if(opp_counter >= 4) {
                    return -8000000;
                }

                score -= 10*opp_counter;
            }
        }
    }

    //check columns
    for(int col = 0; col < 7; ++col) {
        for(int row = 0; row < 3; ++row) {
            int player_counter = 0, opp_counter = 0;
            for(int a = 0; a < 4; ++a) {
                if(given_board.value[col][row+a] == player) {
                    player_counter += 1;
                }
                if(given_board.value[col][row+a] == opp) {
                    opp_counter += 1;
                }
            }

            if(player_counter > 0 && opp_counter > 0) {
                continue;
            }
            else if(player_counter > 0) {
                if(player_counter >= 4) {
                    return 8000000;
                }

                score += 10*player_counter;
            }
            else if(opp_counter > 0) {
                if(opp_counter >= 4) {
                    return -8000000;
                }

                score -= 10*opp_counter;
            }
        }
    }

    //check down right diagonal
    for(int col = 0; col < 4; ++col) {
        for(int row = 0; row < 3; ++row) {
            int player_counter = 0, opp_counter = 0;
            for(int a = 0; a < 4; ++a) {
                if(given_board.value[col+a][row+a] == player) {
                    player_counter += 1;
                }
                if(given_board.value[col+a][row+a] == opp) {
                    opp_counter += 1;
                }
            }

            if(player_counter > 0 && opp_counter > 0) {
                continue;
            }
            else if(player_counter > 0) {
                if(player_counter >= 4) {
                    return 8000000;
                }

                score += 10*player_counter;
            }
            else if(opp_counter > 0) {
                if(opp_counter >= 4) {
                    return -8000000;
                }

                score -= 10*opp_counter;
            }
        }
    }

    //check down left diagonal
    for(int col = 3; col < 7; ++col) {
        for(int row = 0; row < 3; ++row) {
            int player_counter = 0, opp_counter = 0;
            for(int a = 0; a < 4; ++a) {
                if(given_board.value[col-a][row+a] == player) {
                    player_counter += 1;
                }
                if(given_board.value[col-a][row+a] == opp) {
                    opp_counter += 1;
                }
            }

            if(player_counter > 0 && opp_counter > 0) {
                continue;
            }
            else if(player_counter > 0) {
                if(player_counter >= 4) {
                    return 8000000;
                }

                score += 10*player_counter;
            }
            else if(opp_counter > 0) {
                if(opp_counter >= 4) {
                    return -8000000;
                }
                
                score -= 10*opp_counter;
            }
        }
    }

    return score;
}

struct MiniMaxPack {
    int score;
    int col;
    int depth;
};

//choose best worst case scenario
MiniMaxPack minimaxSearch(Board given, char player, int depth, bool isMaximizing) {
    if(depth == 0 || winner(given) != ' ') {
        return (MiniMaxPack){rateBoard(given, player), -1, depth};
    }

    if(isMaximizing) {
        MiniMaxPack best_returned = {-9000000, -1, -1};

        for(int i = 0; i < 7; ++i) {
            if(canDropIntoCol(given, i)) {
                Board copy = given;
                dropIntoCol(copy, player, i);

                MiniMaxPack returned = minimaxSearch(copy, player, depth-1, !isMaximizing);
                if(returned.score > best_returned.score ||
                   (best_returned.score == returned.score && returned.depth > best_returned.depth)) {
                    best_returned.score = returned.score;
                    best_returned.col = i;
                    best_returned.depth = returned.depth;
                }
            }
        }

        return best_returned;
    }
    else {
        MiniMaxPack best_returned = {9000000, -1, -1};

        for(int i = 0; i < 7; ++i) {
            if(canDropIntoCol(given, i)) {
                Board copy = given;
                dropIntoCol(copy, (player=='X')?'O':'X', i);

                MiniMaxPack returned = minimaxSearch(copy, player, depth-1, !isMaximizing);
                if(returned.score < best_returned.score) {
                    best_returned.score = returned.score;
                    best_returned.col = i;
                    best_returned.depth = returned.depth;
                }
            }
        }

        return best_returned;
    }
}

int makeMinimaxMoveAI(Board &given_board, char player) {
    MiniMaxPack returned = minimaxSearch(given_board, player, STEPS_AHEAD, true);
    cout << "chose move with worst case scenario: " << returned.score << endl;
    usleep(1000000);
    dropIntoCol(given_board, player, returned.col);
    return 0;
}

//drops into leftmost available column
int makeBasicMoveAI(Board &given_board, char player) {
    for(int i = 0; i < 7; ++i) {
        int status = dropIntoCol(given_board, player, i);
        if(status == 0) {
            return 0;
        }
    }

    return -1;
}
