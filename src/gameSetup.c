#include <curses.h>

#include "gameSetup.h"
#include "snake.h"
#include "food.h"
#include "display.h"

Snake* snake;

void setupGame(){
    WINDOW *win = initscr();
    curs_set(false); // hide cursor
    start_color();

    init_pair(1, COLOR_GREEN, COLOR_WHITE); // player head colour
    init_pair(2, COLOR_GREEN, COLOR_BLACK); // player body colour
    init_pair(3, COLOR_RED, COLOR_BLACK); // food colour
    init_pair(4, COLOR_WHITE, COLOR_BLACK); // border colour

    keypad(win, true);
    nodelay(win, true); // make getch non-blocking
    
    spawnFood();
    snake = createSnake();
    titleScreen();
}

void stopGame(){
    destroySnake(snake);
    curs_set(true); // give the user their cursor back
    endwin();
}

