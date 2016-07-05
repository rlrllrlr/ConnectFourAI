// + ratings are good for player and - ratings are good for opponent
int rateBoard(char player) {
    int score = 0;

    //check rows
    for(int col = 0; col < 6; ++col) {
        for(int row = 0; row < 7; ++row) {
        }
    }
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
