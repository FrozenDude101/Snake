#include <time.h>
#include <stdbool.h>

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include "colour.h"
#include "display.h"
#include "queue.h"

int kbhit();

bool gameloop(Display* display, struct timespec ts);
void generateApplePosition(Display* display, Queue* snake, int* x, int* y);

int main() {

    Display* display = newDisplay(60, 40, getColourCode("black"), getColourCode("white"));
    hideCursor();

    srandom(time(NULL));

    int fps = 60;
    int ms = 1000 / fps;

    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;

    gameloop(display, ts);

    showCursor();
    freeDisplay(display);

}

// Taken from https://stackoverflow.com/a/22166185.
// I have no clue how this works.
int kbhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF)
    {
      ungetc(ch, stdin);
      return 1;
    }

    return 0;
}

bool gameloop(Display* display, struct timespec ts) {

    Queue* snake = newQueue();
    enqueue(snake, 20, 20);
    enqueue(snake, 20, 20);
    enqueue(snake, 20, 20);
    enqueue(snake, 20, 20);

    int direction = 2;

    int appleX;
    int appleY;
    generateApplePosition(display, snake, &appleX, &appleY);

    int frame = 0;
    bool quit = false;
    while (!quit) {

        if (kbhit()) {
            switch (getchar()) {
                case 'q': quit = true; break;
                case 'w': direction = 3; break;
                case 'a': direction = 0; break;
                case 's': direction = 1; break;
                case 'd': direction = 2; break;
            }

            colourPixel(display, display -> cursorX + 1, display -> cursorY, -1);
        }

        if (frame % 5 == 0) {
            int headX = snake -> tail -> x;
            int headY = snake -> tail -> y;
            switch (direction) {    // Updates head position.
                case 3: headY -= 1; break;
                case 0: headX -= 1; break;
                case 1: headY += 1; break;
                case 2: headX += 1; break;
            }

            // Colours pixels appropriately, removes the end piece, and adds the new head.
            colourPixel(display, snake -> head -> x, snake -> head -> y, -1);
            dequeue(snake);
            colourPixel(display, snake -> tail -> x, snake -> tail -> y, getColourCode("green"));
            enqueue(snake, headX, headY);
            colourPixel(display, snake -> tail -> x, snake -> tail -> y, getColourCode("yellow"));

            // Side wall collision checks.
            if (snake -> tail -> x >= display -> width) quit = true;
            if (snake -> tail -> x < 0) quit = true;
            if (snake -> tail -> y >= display -> height) quit = true;
            if (snake -> tail -> y < 0) quit = true;

            // Self-collision check.
            int* snakeData = getQueueData(snake);
            for (int i = 0; i < queueLength(snake) * 2 - 2; i += 2) {
                int snakeX = snakeData[i];
                int snakeY = snakeData[i + 1];
                if (headX == snakeX && headY == snakeY) {
                    quit = true;
                }
            }
            freeQueueData(snakeData);
        }

        // Apple collision checking.
        int headX = snake -> tail -> x;
        int headY = snake -> tail -> y;
        if (headX == appleX && headY == appleY) {
            enqueueToEnd(snake, snake -> head -> x, snake -> head -> y);
            enqueueToEnd(snake, snake -> head -> x, snake -> head -> y);
            enqueueToEnd(snake, snake -> head -> x, snake -> head -> y);
            generateApplePosition(display, snake, &appleX, &appleY);
            colourPixel(display, headX, headY, getColourCode("yellow"));
        }

        // Nice info.
        writeString(display, "Score:", 1, 1, -1);
        writeInt(display, (queueLength(snake) - 4) / 3 * 10, 5, 1, -1);
        writeString(display, "Used WASD to change direction!", 1, 2, -1);

        frame += 1;
        nanosleep(&ts, NULL);

    }

    writeString(display, "You died :(", 25, 15, -1);
    writeString(display, "Final Score:", 24, 16, -1);
    writeInt(display, (queueLength(snake) - 4) / 3 * 10, 31, 16, -1);
    writeString(display, "Press Q to quit.", 24, 17, -1);

    quit = false;
    while (!quit) {
        if (kbhit()) {
            switch (getchar()) {
                case 'q': quit = true; break;
            }
        }
    }

}

void generateApplePosition(Display* display, Queue* snake, int* x, int* y) {

    bool valid = false;
    do {
        colourPixel(display, *x, *y, -1);
        *x = random() % display -> width;
        *y = random() % display -> height;
        colourPixel(display, *x, *y, getColourCode("red"));

        // The apple can't generate under the snake.
        valid = true;
        int* snakeData = getQueueData(snake);
        for (int i = 0; i < queueLength(snake) * 2; i += 2) {
            int snakeX = snakeData[i];
            int snakeY = snakeData[i + 1];
            if (*x == snakeX && *y == snakeY) {
                valid = false;
                break;
            }
        }
        freeQueueData(snakeData);
    } while (!valid);

}