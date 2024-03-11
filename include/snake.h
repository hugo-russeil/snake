#ifndef SNAKE_H
#define SNAKE_H

typedef struct Snake {
    int x;
    int y;

    int dirX;
    int dirY;

    struct SnakeNode* next;
} Snake;

typedef struct SnakeNode {
    int x;
    int y;

    struct SnakeNode* next;
} SnakeNode;

Snake* createSnake();
void createSnakeNode(Snake* snake);
void destroyTailNode(Snake* snake);
void moveSnake(Snake* snake);
void growSnake(Snake* snake);
void drawSnake(Snake* snake);
bool checkSelfCollision(Snake* snake);
bool checkWallCollision(Snake* snake);
void destroySnake(Snake* snake);

#endif // SNAKE_H