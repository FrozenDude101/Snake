#include <stdio.h>
#include <stdlib.h>

#include "colour.h"


typedef struct Display Display;


struct Display {

    int height;
    int width;
    int scale;

    int backgroundColour;
    int borderColour;

    int cursorX;
    int cursorY;

};


Display* newDisplay(int width, int height, int backgroundColour, int borderColour);
void freeDisplay(Display* display);

void __initDisplay(Display* display);

void __printString(char* string, int foregroundColour, int backgroundColour);
void __newLine();

void hideCursor();
void showCursor();
void moveCursorTo(Display* display, int x, int y);

void writeString(Display* display, char* string, int x, int y, int foregroundColour);
void colourPixel(Display* display, int x, int y, int colour);


Display* newDisplay(int width, int height, int backgroundColour, int borderColour) {

    Display* display = (Display*) malloc(sizeof(Display));

    display -> width = width;
    display -> height = height;
    display -> backgroundColour = backgroundColour;
    display -> borderColour = borderColour;

    display -> cursorX = 0;
    display -> cursorY = 0;

    __initDisplay(display);

    return display;

}
void freeDisplay(Display* display) {

    resetColour();
    system("clear");

    free(display);

}

void __initDisplay(Display* display) {

    int width = display -> width;
    int height = display -> height;

    system("clear");

    for (int i = 0; i < width + 2; i++) {
        __printString("  ", -1, display -> borderColour);
    }
    __newLine();

    for (int i = 0; i < height; i++) {
        __printString("  ", -1, display -> borderColour);
        for (int j = 0; j < width; j++) {
            __printString("  ", -1, display -> backgroundColour);
        }
        __printString("  ", -1, display -> borderColour);
        __newLine();
    }

    for (int i = 0; i < width + 2; i++) {
        __printString("  ", -1, display -> borderColour);
    }
    __newLine();

}

void __printString(char* string, int foregroundColour, int backgroundColour) {

    setForeground(foregroundColour);
    setBackground(backgroundColour);

    printf("%s", string);
    resetColour();

    fflush(stdout);

}
void __newLine() {

    __printString("\n", -1, -1);

}

void hideCursor() {
    
    printf("\e[?25l");

}
void showCursor() {

    printf("\e[?25h");

}
void moveCursorTo(Display* display, int x, int y) {

    if (x < 0) x = 0;
    if (x >= display -> width) x = display -> width - 1;

    if (y < 0) y = 0;
    if (y >= display -> height) y = display -> height - 1;

    display -> cursorX = x;
    display -> cursorY = y;

    x *= 2;
    x += 3;
    y += 2;

    printf("\x1B[%d;%df", y, x);

}

void writeString(Display* display, char* string, int x, int y, int foregroundColour) {

    moveCursorTo(display, x, y);
    __printString(string, foregroundColour, display -> backgroundColour);

}
void writeInt(Display* display, int num, int x, int y, int foregroundColour) {

    char s[10];
    sprintf(s, "%d", num);
    writeString(display, s, x, y, foregroundColour);

}
void colourPixel(Display* display, int x, int y, int colour) {

    if (colour == -1) colour = display -> backgroundColour;
    writeString(display, "██", x, y, colour);

}
void clearDisplay(Display* display) {

    for (int i = 0; i < display -> width; i++) {
        for (int j = 0; j < display -> height; j++) {
            colourPixel(display, i, j, display -> backgroundColour);
        }
    }

}