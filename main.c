#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define MAX_LENGTH 104

int score = 0;
int timeDelay = 200; //Default hardness

typedef enum direction{
    UP,
    DOWN,
    RIGHT,
    LEFT
}direction;

direction dir = RIGHT;

typedef struct {
    int x;
    int y;
} coords;

typedef struct{
    coords body[MAX_LENGTH];
    char shape[MAX_LENGTH];
} snake;

typedef struct{
    int x;
    int y;
    char shape;
}food;

food Food;

void goToXY(int x, int y);
void getTerminalSize(int *rows, int *cols);
void updateScene(snake *Snake);
void getInput(void);
void drawWalls(void);
void hideCursor(void);

int main()
{
    hideCursor();
    snake Snake;
    int rows, cols;
    getTerminalSize(&rows, &cols); //30 ,120 for my terminal
    int input;
    int choiseOfLevel;
    while(1){
        //initializing food's location and shape
        Food.shape = '#';
        Food.x = (rand() % 118) + 1;
        Food.y = (rand() % 28)  + 1;
        char playerStatus = 0; //default
        printf("Snake game\n1. Start game\n2. Levels\n3. Exit game\nEnter your choice: ");
        scanf("%d", &input);
        switch(input){
        case 1:
            for(int i = 0; i < 4; i++){
                Snake.body[i].x = 23 - i;
                Snake.body[i].y = 15;
                if(i == 0)
                    Snake.shape[i] = '@';
                else
                    Snake.shape[i] = 'O';
                }
            while(1){
                updateScene(&Snake);
                Sleep(timeDelay);
                for(int i = 1; i < (score+4); i++)
                    if((Snake.body[0].x == Snake.body[i].x && Snake.body[0].y == Snake.body[i].y) || Snake.body[0].y == 0 || Snake.body[0].y == 29 || Snake.body[0].x == 0 || Snake.body[0].x == 119){
                        playerStatus = 1;
                        break;
                    }else if(score == 100){
                        playerStatus = 2;
                        break;
                    }
                if(playerStatus == 1) {
                    system("cls");
                    goToXY(56, 15);
                    printf("Game Over");
                    goToXY(56, 16);
                    printf("Press 'r' to restart or 'q' to quit.");
                    char choice = _getch();
                    if (choice == 'r' || choice == 'R') {
                        playerStatus = 0;
                        score = 0;
                        dir = RIGHT;
                        for(int i = 0; i < 4; i++){
                            Snake.body[i].x = 23 - i;
                            Snake.body[i].y = 15;
                            if(i == 0)
                                Snake.shape[i] = '@';
                            else
                                Snake.shape[i] = 'O';
                            }
                        break;
                    } else if (choice == 'q' || choice == 'Q') {
                        printf("\n");
                        exit(0);
                    }
                } else if(playerStatus == 2) {
                    system("cls");
                    goToXY(56, 15);
                    printf("You WON");
                    goToXY(56, 16);
                    printf("Press 'r' to restart or 'q' to quit.");
                    char choice = _getch();
                    if (choice == 'r' || choice == 'R') {
                        score = 0;
                        playerStatus = 0;
                        dir = RIGHT;
                        for(int i = 0; i < 4; i++){
                            Snake.body[i].x = 23 - i;
                            Snake.body[i].y = 15;
                            if(i == 0)
                                Snake.shape[i] = '@';
                            else
                                Snake.shape[i] = 'O';
                            }
                        break;
                    } else if (choice == 'q' || choice == 'Q') {
                        exit(0);
                        printf("\n");
                    }
                }
            }
            printf("\n");
            break;
        case 2:
            printf("Level\n1. Easy\n2. Medium\n3. Hard\nEnter your choice: ");
            scanf("%d", &choiseOfLevel);
            switch(choiseOfLevel){
            case 1:
                timeDelay = 200; break;
            case 2:
                timeDelay = 120; break;
            case 3:
                timeDelay = 60; break;
            default:
                printf("Default Level: Easy\n");
                timeDelay = 200; break;
            }
            break;
        case 3:
            exit(0);
            break;
        default:
            printf("\nInvalid choice!!!");
            break;
        }
    }
}


void goToXY(int x, int y){
    COORD coord = {.X = x, .Y = y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void getTerminalSize(int *rows, int *cols) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *cols = csbi.dwSize.X;
    *rows = csbi.dwSize.Y;
}

void updateScene(snake *Snake){
    system("cls");
    drawWalls();
    goToXY(Food.x, Food.y);
    printf("%c", Food.shape);
    if(Snake->body[0].x == Food.x && Snake->body[0].y == Food.y){
        score++;
        Snake->shape[score + 3] = 'O';
        Food.x = (rand() % 118) + 1;
        Food.y = (rand() % 28)  + 1;
    }
    getInput();
    for(int i = (score+3); i > 0; i--)
    {
        Snake->body[i].x = Snake->body[i-1].x;
        Snake->body[i].y = Snake->body[i-1].y;
    }
    switch(dir){
        case UP:
            Snake->body[0].y--;
            break;
        case DOWN:
                Snake->body[0].y++;
            break;
        case RIGHT:
                Snake->body[0].x++;
            break;
        default:
                Snake->body[0].x--;
            break;
    }

    for(int i = 0; i < (score+4); i++){
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
                case 72:
                    if(dir != DOWN)
                        dir = UP;
                    break;
                case 80:
                    if(dir != UP)
                        dir = DOWN;
                    break;
                case 75:
                    if(dir != RIGHT)
                        dir = LEFT;
                    break;
                case 77:
                    if(dir != LEFT)
                        dir = RIGHT;
                    break;
            }
        }
    }
}

void drawWalls(void){
    for(int y = 0; y < 30; y++)
        for(int x = 0; x < 120; x++)
            if(x == 0 || x == 119 || ((y == 0) && ((x < 53) || (x > 65))) || y == 29){
                goToXY(x,y);
                printf("%c",  219);
            }
    goToXY(53, 0);
    printf(" Score : %d ", score);
}

void hideCursor(void) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;  // Set cursor visibility to FALSE
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}
