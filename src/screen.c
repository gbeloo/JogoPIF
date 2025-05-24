#include "screen.h"
#include <stdio.h>

void screenInit(int drawBorders) {
    screenClear();
    screenHideCursor();
    screenSetNormal();

    if (drawBorders) {
        screenBoxEnable();
        for (int x = SCRSTARTX; x <= SCRENDX; x++) {
            screenGotoxy(x, SCRSTARTY);
            putchar(BOX_HLINE);
            screenGotoxy(x, SCRENDY);
            putchar(BOX_HLINE);
        }
        for (int y = SCRSTARTY; y <= SCRENDY; y++) {
            screenGotoxy(SCRSTARTX, y);
            putchar(BOX_VLINE);
            screenGotoxy(SCRENDX, y);
            putchar(BOX_VLINE);
        }
        screenGotoxy(SCRSTARTX, SCRSTARTY);
        putchar(BOX_UPLEFT);
        screenGotoxy(SCRENDX, SCRSTARTY);
        putchar(BOX_UPRIGHT);
        screenGotoxy(SCRSTARTX, SCRENDY);
        putchar(BOX_DWNLEFT);
        screenGotoxy(SCRENDX, SCRENDY);
        putchar(BOX_DWNRIGHT);
        screenBoxDisable();
    }
    screenUpdate();
}

void screenDestroy() {
    screenSetNormal();
    screenShowCursor();
    screenClear();
    screenUpdate();
}

void screenGotoxy(int x, int y) {
    printf("%s[%d;%dH", ESC, y, x);
}

void screenSetColor(screenColor fg, screenColor bg) {
    int code_fg = (fg < 8 ? 30 + fg : 90 + (fg - 8));
    int code_bg = (bg < 8 ? 40 + bg : 100 + (bg - 8));
    printf("%s[%d;%dm", ESC, code_fg, code_bg);
}
