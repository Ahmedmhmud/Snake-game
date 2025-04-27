#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <windows.h>

#define MAX_LENGTH 104

extern int score;
extern int timeDelay;

typedef enum direction {
    UP,
    DOWN,
    RIGHT,
    LEFT
} direction;

typedef struct {
    int x;
    int y;
} coords;

typedef struct {
    coords body[MAX_LENGTH];
    char shape[MAX_LENGTH];
} snake;

typedef struct {
    int x;
    int y;
    char shape;
} food;

extern food Food;
extern direction dir;

// Function prototypes
void goToXY(int x, int y);
void getTerminalSize(int *rows, int *cols);
void updateScene(snake *Snake);
void getInput(void);
void drawWalls(void);
void hideCursor(void);
void initializeSnake(snake *Snake);

#endif // SNAKE_H
