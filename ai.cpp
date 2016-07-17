#include <iostream>
#include <unistd.h>
using namespace std;

#define STEPS_AHEAD 4

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

                score += player_counter*10;
            }
            else if(opp_counter > 0) {
                if(opp_counter >= 4) {
                    return -8000000;
                }

                score -= opp_counter*10;
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

                score += player_counter*10;
            }
            else if(opp_counter > 0) {
                if(opp_counter >= 4) {
                    return -8000000;
                }

                score -= opp_counter*10;
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

                score += player_counter*10;
            }
            else if(opp_counter > 0) {
                if(opp_counter >= 4) {
                    return -8000000;
                }

                score -= opp_counter*10;
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

                score += player_counter*10;
            }
            else if(opp_counter > 0) {
                if(opp_counter >= 4) {
                    return -8000000;
                }
                
                score -= opp_counter*10;
            }
        }
    }

    return score;
}


//choose best worst case scenario
int minimaxSearch(Board given, char player, int depth, bool isMaximizing) {
    if(depth == 0 || winner(given) != ' ') {
        return rateBoard(given, player);
    }

    if(isMaximizing) {
        int max_score = -9000000, best_col = -1;
        for(int i = 0; i < 7; ++i) {
            if(canDropIntoCol(given, i)) {
                Board copy = given;
                dropIntoCol(copy, player, i);

                int score = minimaxSearch(copy, player, depth-1, !isMaximizing);
                if(score > max_score) {
                    max_score = score;
                    best_col = i;
                }
            }
        }

        if(depth == STEPS_AHEAD) {
            cout << "chose move with score: " << max_score << endl;
            //usleep(1000000);
            return best_col;
        }
        else {
            return max_score;
        }
    }
    else {
        int min_score = 9000000, best_col = -1;
        for(int i = 0; i < 7; ++i) {
            if(canDropIntoCol(given, i)) {
                Board copy = given;
                dropIntoCol(copy, (player=='X')?'O':'X', i);

                int score = minimaxSearch(copy, player, depth-1, !isMaximizing);
                if(score < min_score) {
                    min_score = score;
                    best_col = i;
                }
            }
        }

        return min_score;
    }
}

int makeMinimaxMoveAI(Board &given_board, char player) {
    int move = minimaxSearch(given_board, player, STEPS_AHEAD, true);
    dropIntoCol(given_board, player, move);
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
