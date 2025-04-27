#include <stdio.h>
#include <stdlib.h>
#include "snakeGame.h"

int main() {
    hideCursor();
    snake Snake;
    int rows, cols;
    getTerminalSize(&rows, &cols);
    int input;
    int choiceOfLevel;

    while (1) {
        Food.shape = '#';
        Food.x = (rand() % 118) + 1;
        Food.y = (rand() % 28) + 1;
        char playerStatus = 0;

        printf("Snake game\n1. Start game\n2. Levels\n3. Exit game\nEnter your choice: ");
        scanf("%d", &input);

        switch (input) {
            case 1:
                system("cls");
                initializeSnake(&Snake);
                drawWalls();
                while (1) {
                    updateScene(&Snake);
                    Sleep(timeDelay);

                    for (int i = 1; i < (score + 4); i++) {
                        if ((Snake.body[0].x == Snake.body[i].x && Snake.body[0].y == Snake.body[i].y) ||
                            Snake.body[0].y == 0 || Snake.body[0].y == 29 ||
                            Snake.body[0].x == 0 || Snake.body[0].x == 119) {
                            playerStatus = 1;
                            break;
                        } else if (score == 100) {
                            playerStatus = 2;
                            break;
                        }
                    }

                    if (playerStatus == 1 || playerStatus == 2) {
                        system("cls");
                        if (playerStatus == 1) {
                            goToXY(56, 15);
                            printf("Game Over");
                        } else {
                            goToXY(56, 15);
                            printf("You WON");
                        }
                        goToXY(50, 16);
                        printf("Press 'r' to restart or 'q' to quit.");
                        char choice = _getch();
                        if (choice == 'r' || choice == 'R') {
                            system("cls");
                            playerStatus = 0;
                            score = 0;
                            dir = RIGHT;
                            initializeSnake(&Snake);
                            break;
                        } else if (choice == 'q' || choice == 'Q') {
                            exit(0);
                        }
                    }
                }
                break;

            case 2:
                printf("Level\n1. Easy\n2. Medium\n3. Hard\nEnter your choice: ");
                scanf("%d", &choiceOfLevel);
                switch (choiceOfLevel) {
                    case 1:
                        timeDelay = 200;
                        break;
                    case 2:
                        timeDelay = 120;
                        break;
                    case 3:
                        timeDelay = 60;
                        break;
                    default:
                        printf("Default Level: Easy\n");
                        timeDelay = 200;
                        break;
                }
                break;

            case 3:
                exit(0);
                break;

            default:
                printf("\nInvalid choice!!!\n");
                break;
        }
    }
}
