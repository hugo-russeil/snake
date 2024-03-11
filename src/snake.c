#include <stdlib.h>
#include <curses.h>

#include "snake.h"

Snake* createSnake(){
    Snake* snake = malloc(sizeof(Snake));
    if(snake == NULL) return NULL;
    snake->x = COLS / 2;
    snake->y = LINES / 2;
    snake->dirX = 0;
    snake->dirY = 0;
    snake->next = NULL;
    return snake;
}

void createSnakeNode(Snake* snake){
    if(snake == NULL) return;
    SnakeNode* node = malloc(sizeof(SnakeNode));
    if(node == NULL) return;
    node->next = snake->next;
    snake->next = node;  // the new node is inserted at the second position
    node->x = snake->x; // the new node will be created at the same position as the head
    node->y = snake->y;
}

void destroyTailNode(Snake* snake){
    if(snake == NULL) return;
    SnakeNode* node = snake->next;
    if (node->next == NULL){
        free(node);
        snake->next = NULL;
        return;
    }
    while(node->next->next != NULL){
        node = node->next;
    }
    free(node->next);
    node->next = NULL;
}

void moveSnake(Snake *snake){
    if(snake->next != NULL){
        createSnakeNode(snake);
        destroyTailNode(snake);
    }
    snake->x += snake->dirX * 2; // multiply by 2 because terminal characters are twice as tall as they are wide
    snake->y += snake->dirY;
}

void growSnake(Snake* snake){
    if(snake == NULL) return;
    createSnakeNode(snake);
    snake->x += snake->dirX * 2;
    snake->y += snake->dirY;
}

void drawSnake(Snake* snake){
    if(snake == NULL) return;

    attron(COLOR_PAIR(1));
    mvaddch(snake->y, snake->x, ACS_CKBOARD);
    mvaddch(snake->y, snake->x + 1, ACS_CKBOARD);
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    SnakeNode* node = snake->next;
    while(node != NULL){
        mvaddch(node->y, node->x, ACS_CKBOARD);
        mvaddch(node->y, node->x + 1, ACS_CKBOARD);
        if(node->next != NULL) node = node->next;
        else break;
    }
    attroff(COLOR_PAIR(2));
}

bool checkSelfCollision(Snake* snake){
    if(snake == NULL) return NULL;
    if(snake->next == NULL) return false;
    SnakeNode* node = snake->next;
    while(node != NULL){
        if(node->x == snake->x && node->y == snake->y) return true;
        node = node->next;
    }
    return false;
}

bool checkWallCollision(Snake* snake){
    if(snake == NULL) return NULL;
    if(snake->x <= 0 || snake->x >= COLS - 2|| snake->y <= 0 || snake->y >= LINES - 1) return true;
    return false;
}

void destroySnake(Snake* snake){
    while(snake->next != NULL){
        destroyTailNode(snake);
    }
    free(snake);
}
