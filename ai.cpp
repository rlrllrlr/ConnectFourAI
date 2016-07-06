// + ratings are good for player and - ratings are good for opponent
int rateBoard(char player) {
    char opp = (player == 'X')?'O':'X';

    int score = 0;

    //check rows
    for(int row = 0; row < 6; ++row) {
        for(int col = 0; col < 7-3; ++col) {

            int player_counter = 0, opp_counter = 0;
            for(int a = 0; a < 4; ++a) {
                if(board[col+a][row] == player) {
                    player_counter += 1;
                }
                if(board[col+a][row] == opp) {
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
                if(board[col][row+a] == player) {
                    player_counter += 1;
                }
                if(board[col][row+a] == opp) {
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
                if(board[col+a][row+a] == player) {
                    player_counter += 1;
                }
                if(board[col+a][row+a] == opp) {
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
                if(board[col-a][row+a] == player) {
                    player_counter += 1;
                }
                if(board[col+a][row+a] == opp) {
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

//drops into leftmost available column
int makeBasicMoveAI(char player) {
    for(int i = 0; i < 7; ++i) {
        int status = dropIntoCol(player, i);
        if(status == 0) {
            return 0;
        }
    }

    return -1;
}
