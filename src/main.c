/**
 * main.c
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
 */

#include <stdio.h>
#include <string.h>

#include <screen.h>
#include <keyboard.h>
#include <timer.h>

int x = 34, y = 12;
int incX = 1, incY = 1;

void printHello(int nextX, int nextY)
{
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(x, y);
    printf("           ");
    x = nextX;
    y = nextY;
    screenGotoxy(x, y);
    printf("Hello World");
}

void printKey(int ch)
{
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(35, 22);
    printf("Key code :");

    screenGotoxy(34, 23);
    printf("            ");
    
    if (ch == 27) screenGotoxy(36, 23);
    else          screenGotoxy(39, 23);

    printf("%d ", ch);
    while (keyhit()) {
        printf("%d ", readch());
    }
}

int main() 
{
    static int ch = 0;
    static long timer = 0;

    screenInit(1);
    keyboardInit();
    timerInit(50);

    printHello(x, y);
    screenUpdate();

    while (ch != 10 && timer <= 100) // enter ou 5s
    {
        if (keyhit()) {
            ch = readch();
            printKey(ch);
            screenUpdate();
        }

        if (timerTimeOver() == 1) {
            int newX = x + incX;
            if (newX >= (MAXX - strlen("Hello World") - 1) || newX <= MINX + 1)
                incX = -incX;
            int newY = y + incY;
            if (newY >= MAXY - 1 || newY <= MINY + 1)
                incY = -incY;

            printHello(newX, newY);
            screenUpdate();
            timer++;
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
