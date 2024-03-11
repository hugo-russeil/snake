#include <curses.h>
#include <string.h>

#include "display.h"
#include "snake.h"
#include "food.h"
#include "score.h"
#include "gameSetup.h"

char* title[] = {
    " ____              _        ",
    "/ ___| _ __   __ _| | _____ ",
    "\\___ \\| '_ \\ / _` | |/ / _ \\",
    " ___) | | | | (_| |   <  __/",
    "|____/|_| |_|\\__,_|_|\\_\\___|"
};

char* gameOver[] = {
    "",
    "",
    "  ____                         ___                 ",
    " / ___| __ _ _ __ ___   ___   / _ \\__   _____ _ __ ",
    "| |  _ / _` | '_ ` _ \\ / _ \\ | | | \\ \\ / / _ \\ '__|",
    "| |_| | (_| | | | | | |  __/ | |_| |\\ V /  __/ |   ",
    " \\____|\\__,_|_| |_| |_|\\___|  \\___/  \\_/ \\___|_|   ",
    "",
    ""
};

void titleScreen(){
    erase();
    int offset;
    for(int i = 0; i < sizeof(title) / sizeof(title[0]); i++){
        offset = (COLS - strlen(title[i])) / 2;
        mvprintw(i, offset, "%s", title[i]);
    }

    mvprintw(5, offset, "by Hugo Russeil");

    offset = (COLS - strlen("Press return key to start")) / 2;
    mvprintw(19, offset, "Press return key to start");

    while(getch() != '\n'); // wait for the user to press the return key
}

void drawBorders(){ // draw the borders on the edges of the terminal window
    attron(COLOR_PAIR(4));
    for(int i = 0; i < COLS; i++){
        mvaddch(0, i, ACS_CKBOARD);
        mvaddch(LINES - 1, i, ACS_CKBOARD);
    }
    for(int i = 0; i < LINES; i++){
        mvaddch(i, 0, ACS_CKBOARD);
        mvaddch(i, 1, ACS_CKBOARD);
        mvaddch(i, COLS - 2, ACS_CKBOARD);
        mvaddch(i, COLS - 1, ACS_CKBOARD);
    }
    attroff(COLOR_PAIR(4));
}

void drawGame(Snake* snake){
    erase();
    drawBorders();
    drawSnake(snake);
    drawFood();
    displayScore();
    refresh();
}

void gameOverScreen(){
    erase();
    int offset;
    for(int i = 0; i < sizeof(gameOver) / sizeof(gameOver[0]); i++){
        offset = (COLS - strlen(gameOver[i])) / 2;
        mvprintw(i + 5, offset, "%s", gameOver[i]);
    }

    offset = (COLS - strlen("Press 'q' to quit")) / 2;
    mvprintw(20, offset, "Press 'q' to quit");
    while(getch() != 'q');
}
