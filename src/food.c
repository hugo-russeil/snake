#include <stdlib.h>
#include <curses.h>

#include "food.h"

int foodX;
int foodY;

void spawnFood(){
    foodX = ((rand() % ((COLS - 2) / 2)) * 2); // divide then multiply by 2 to ensure the food is spawned on an even column
    foodY = ((rand() % ((LINES - 2) / 2) + 1) * 2); // -2 to prevent the food from being spawned on the border,
}                                               

void drawFood(){
    attron(COLOR_PAIR(3));
    mvaddch(foodY, foodX, ACS_CKBOARD);
    mvaddch(foodY, foodX + 1, ACS_CKBOARD);
    attroff(COLOR_PAIR(3));
}
