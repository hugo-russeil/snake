#include <curses.h>
#include <stdlib.h>

#include "snake.h"
#include "food.h"
#include "gameSetup.h"
#include "display.h"
#include "score.h"
#include "timer.h"

void main() {

    if(setupGame() == 0) return;

    while(1){
        
        switch(getch()){
            case KEY_UP:
                // check if the user is trying to do a 180 (which is not allowed),
                // or to move in the direction he is already moving (which is useless)
                if((snake->next != NULL && snake->dirY == 1) || (snake->dirX == 0 && snake->dirY == -1)){
                    flushinp(); // clear the input buffer to prevent the user from queuing up too many inputs
                    break;      // which would result in latency in the resolution of the inputs
                }
                snake->dirX = 0;                                   
                snake->dirY = -1;                             
                break;
            case KEY_DOWN:
                if((snake->next != NULL && snake->dirY == -1) || (snake->dirX == 0 && snake->dirY == 1)){
                    flushinp();
                    break;
                }
                snake->dirX = 0;
                snake->dirY = 1;
                break;
            case KEY_LEFT:
                if((snake->next != NULL && snake->dirX == 1) || (snake->dirX == -1 && snake->dirY == 0)){
                    flushinp();
                    break;
                }
                snake->dirX = -1;
                snake->dirY = 0;
                break;
            case KEY_RIGHT:
                if((snake->next != NULL && snake->dirX == -1) || (snake->dirX == 1 && snake->dirY == 0)){
                    flushinp();
                    break;
                }
                snake->dirX = 1;
                snake->dirY = 0;
                break;
            case ' ':
                while(getch() != ' ');
                break;
            case 'q':
                stopGame();
                return;
        }

        if(snake->x == foodX && snake->y == foodY){
            growSnake(snake);
            incrementScore();
            setupTimer(&waitTime, calculateWaitTime(score));
            spawnFood();
        }else moveSnake(snake);

        if(checkSelfCollision(snake) || checkWallCollision(snake)){
            setupTimer(&waitTime, 500000000);
            nanosleep(&waitTime, NULL); // freeze the game for half a second to give the user time to see the collision
            gameOverScreen();
            stopGame();
            return;
        }

        drawGame(snake);
        nanosleep(&waitTime, NULL);
    }

    stopGame();
    return;
}
