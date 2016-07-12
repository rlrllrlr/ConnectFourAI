// + ratings are good for player and - ratings are good for opponent
int rateBoard(Board given_board, char player) {
    char opp = (player == 'X')?'O':'X';

    int score = 0;

    //check rows
    for(int row = 0; row < 6; ++row) {
        for(int col = 0; col < 7-3; ++col) {

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
                    return 8000;
                }

                score += player_counter*10;
            }
            else if(opp_counter > 0) {
                if(opp_counter >= 4) {
                    return -8000;
                }

                score -= opp_counter*10;
            }
        }
    }

    //check columns
    for(int col = 0; col < 7; ++col) {
        for(int row = 0; row < 6-3; ++row) {
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
                    return 8000;
                }

                score += player_counter*10;
            }
            else if(opp_counter > 0) {
                if(opp_counter >= 4) {
                    return -8000;
                }

                score -= opp_counter*10;
            }
        }
    }

    //check down right diagonal
    for(int col = 0; col < 7-3; ++col) {
        for(int row = 0; row < 6-3; ++row) {
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
                    return 8000;
                }

                score += player_counter*10;
            }
            else if(opp_counter > 0) {
                if(opp_counter >= 4) {
                    return -8000;
                }

                score -= opp_counter*10;
            }
        }
    }

    //check down left diagonal
    for(int col = 3; col < 7; ++col) {
        for(int row = 0; row < 6-3; ++row) {
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
                    return 8000;
                }

                score += player_counter*10;
            }
            else if(opp_counter > 0) {
                if(opp_counter >= 4) {
                    return -8000;
                }
                
                score -= opp_counter*10;
            }
        }
    }

    return score;
}

int minimaxSearch(Board given, char player, int depth=0) {
    //if root, find the child with best minimax search result
    if(depth == 0) {
        int max_score = -9000, best_col = 0;
        for(int i = 0; i < 7; ++i) {
            if(canDropIntoCol(given, i)) {
                Board copy = given;
                dropIntoCol(copy, player, i);

                int score = minimaxSearch(copy, (player=='X')?'O':'X', depth+1);
                if(score > max_score) {
                    max_score = score;
                    best_col = i;
                }
            }
        }

        return best_col;
    }
    else {
        if(depth == 6) {
            return rateBoard(given, player);
        }

        int max_score = -9000, best_col = 0;
        for(int i = 0; i < 7; ++i) {
            if(canDropIntoCol(given, i)) {
                Board copy = given;
                dropIntoCol(copy, player, i);

                int score = rateBoard(copy, player);
                if(score > max_score) {
                    max_score = score;
                    best_col = i;
                }
            }
        }

        Board copy = given;
        dropIntoCol(copy, player, best_col);

        return minimaxSearch(copy, (player=='X')?'O':'X', depth+1);
    }
}

int makeMinimaxMoveAI(Board &given_board, char player) {
    int move = minimaxSearch(given_board, player);
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
