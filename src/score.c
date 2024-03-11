#include <curses.h>

#include "score.h"

int score = 0;

void displayScore(){
    mvprintw(1, COLS - 12, "Score: %d", score);
}

void incrementScore(){
    score++;
}
