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
