#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "snakeGame.h"

int score = 0;
int timeDelay = 200; // Default hardness
food Food;
direction dir = RIGHT;

void goToXY(int x, int y) {
    COORD coord = { .X = x, .Y = y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void getTerminalSize(int *rows, int *cols) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *cols = csbi.dwSize.X;
    *rows = csbi.dwSize.Y;
}

void updateScene(snake *Snake) {
    goToXY(Food.x, Food.y);
    printf("%c", Food.shape);

    if (Snake->body[0].x == Food.x && Snake->body[0].y == Food.y) {
        score++;
        Snake->shape[score + 3] = 'O';
        Food.x = (rand() % 118) + 1;
        Food.y = (rand() % 28) + 1;
    }

    getInput();
    goToXY(Snake->body[score + 3].x, Snake->body[score + 3].y);
    printf(" ");

    for (int i = (score + 3); i > 0; i--) {
        Snake->body[i].x = Snake->body[i - 1].x;
        Snake->body[i].y = Snake->body[i - 1].y;
    }

    switch (dir) {
        case UP:
            Snake->body[0].y--;
            break;
        case DOWN:
            Snake->body[0].y++;
            break;
        case RIGHT:
            Snake->body[0].x++;
            break;
        case LEFT:
            Snake->body[0].x--;
            break;
    }

    goToXY(62, 0);
    printf("%d ", score);

    for (int i = 0; i < (score + 4); i++) {
        goToXY(Snake->body[i].x, Snake->body[i].y);
        printf("%c", Snake->shape[i]);
    }
}

void getInput(void) {
    if (_kbhit()) {
        int ch = _getch();
        if (ch == 224) {
            ch = _getch();
            switch (ch) {
                case 72: if (dir != DOWN) dir = UP; break;
                case 80: if (dir != UP) dir = DOWN; break;
                case 75: if (dir != RIGHT) dir = LEFT; break;
                case 77: if (dir != LEFT) dir = RIGHT; break;
            }
        }
    }
}

void drawWalls(void) {
    for (int y = 0; y < 30; y++)
        for (int x = 0; x < 120; x++)
            if (x == 0 || x == 119 || ((y == 0) && ((x < 53) || (x > 65))) || y == 29) {
                goToXY(x, y);
                printf("%c", 219);
            }
    goToXY(53, 0);
    printf(" Score : ");
}

void hideCursor(void) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void initializeSnake(snake *Snake) {
    for (int i = 0; i < 4; i++) {
        Snake->body[i].x = 23 - i;
        Snake->body[i].y = 15;
        Snake->shape[i] = (i == 0) ? '@' : 'O';
    }
}

