#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>   // for getch() and kbhit() on Windows
#include <windows.h> // for Sleep()

#define WIDTH 30
#define HEIGHT 20

int gameOver;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int tailLen;
int dir; // 0 stop, 1 left, 2 right, 3 up, 4 down

void setup() {
    gameOver = 0;
    dir = 0;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    score = 0;
}

void draw() {
    system("cls");

    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0) printf("#");

            if (i == y && j == x) printf("O");
            else if (i == fruitY && j == fruitX) printf("F");
            else {
                int printTail = 0;
                for (int k = 0; k < tailLen; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o");
                        printTail = 1;
                        break;
                    }
                }
                if (!printTail) printf(" ");
            }

            if (j == WIDTH - 1) printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");
    printf("score: %d\n", score);
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': dir = 1; break;
            case 'd': dir = 2; break;
            case 'w': dir = 3; break;
            case 's': dir = 4; break;
            case 'x': gameOver = 1; break;
        }
    }
}

void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < tailLen; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case 1: x--; break;
        case 2: x++; break;
        case 3: y--; break;
        case 4: y++; break;
    }

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) gameOver = 1;

    for (int i = 0; i < tailLen; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = 1;
        }
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        tailLen++;
    }
}

int main() {
    srand(time(0));
    setup();

    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(60);  // control speed
    }

    system("cls");
    printf("Game Over!\nScore: %d\n", score);
    return 0;
}
