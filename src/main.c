#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

#include "snake.h"
#include "food.h"
#include "gameSetup.h"
#include "display.h"

void main() {
    
    setupGame();

    while(1){

        switch(getch()){
            case KEY_UP:
                if(snake->next != NULL && snake->dirY == 1) break; // prevent the snake from reversing into itself
                snake->dirX = 0;                                   // if the snake is longer than 1 node
                snake->dirY = -1;                                  // in which case it can reverse
                break;
            case KEY_DOWN:
                if(snake->next != NULL && snake->dirY == -1) break;
                snake->dirX = 0;
                snake->dirY = 1;
                break;
            case KEY_LEFT:
                if(snake->next != NULL && snake->dirX == 1) break;
                snake->dirX = -1;
                snake->dirY = 0;
                break;
            case KEY_RIGHT:
                if(snake->next != NULL && snake->dirX == -1) break;
                snake->dirX = 1;
                snake->dirY = 0;
                break;
            case 'q':
                stopGame();
                return;
        }

        if(snake->x == foodX && snake->y == foodY){
            growSnake(snake);
            spawnFood();
        }else moveSnake(snake);

        if(checkSelfCollision(snake) || checkWallCollision(snake)){
            usleep(500000); // freeze the game for half a second to give the user time to see the collision
            gameOverScreen();
            stopGame();
            return;
        }

        drawGame(snake);

        usleep(100000);
    }

    stopGame();
    return;
}
