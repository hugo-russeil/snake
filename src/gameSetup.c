#include <curses.h>
#include <time.h>

#include "gameSetup.h"
#include "snake.h"
#include "food.h"
#include "display.h"
#include "timer.h"

Snake* snake;

int setupGame(){
    WINDOW *win = initscr();
    if(win == NULL){
        fprintf(stderr, "Error initialising ncurses.\n");
        return 0;
    }
    curs_set(false); // hide cursor
    start_color();

    init_pair(1, COLOR_GREEN, COLOR_WHITE); // player head colour
    init_pair(2, COLOR_GREEN, COLOR_BLACK); // player body colour
    init_pair(3, COLOR_RED, COLOR_BLACK); // food colour
    init_pair(4, COLOR_WHITE, COLOR_BLACK); // border colour

    keypad(win, true);
    nodelay(win, true); // make getch non-blocking

    setupTimer(&waitTime, 100000000);
    
    spawnFood();
    snake = createSnake();
    titleScreen();
    return 1;
}

void stopGame(){
    destroySnake(snake);
    curs_set(true); // give the user their cursor back
    endwin();
}

