#ifndef COLOUR_HEADER_LOADED

#define COLOUR_HEADER_LOADED 1

#include <stdio.h>
#include <stdlib.h>

int getColourCode(char* colour);
void setForeground(int id);
void setBackground(int id);
void resetColour();

int getColourCode(char* colour) {

    if (colour == "black") return 0;
    else if (colour == "red") return 1;
    else if (colour == "green") return 2;
    else if (colour == "yellow") return 3;
    else if (colour == "blue") return 4;
    else if (colour == "magenta") return 5;
    else if (colour == "cyan") return 6;
    else if (colour == "white") return 7;
    
    printf("Invalid colour '%s'.", colour);
    printf("Valid colours: black, red, green, yellow, blue, magenta, cyan, white.\n");
    exit(EXIT_FAILURE);

}

void setForeground(int id) {

    switch (id) {
        case -1:                // Default
            break;
        case 0:                 // Black
            printf("\033[30m");
            break;
        case 1:                 // Red
            printf("\033[31m");
            break;
        case 2:                 // Green
            printf("\033[32m");
            break;
        case 3:                 // Yellow
            printf("\033[33m");
            break;
        case 4:                 // Blue
            printf("\033[34m");
            break;
        case 5:                 // Magenta
            printf("\033[35m");
            break;
        case 6:                 // Cyan
            printf("\033[36m");
            break;
        case 7:                 // White
            printf("\033[37m");
            break;
        default:
            printf("Invalid colour code '%d'.", id);
            printf("Valid colour codes: 0-8.\n");
            exit(EXIT_FAILURE);
    }

}
void setBackground(int id) {

    switch (id) {
        case -1:                // Default
            break;
        case 0:                 // Black
            printf("\033[40m");
            break;
        case 1:                 // Red
            printf("\033[41m");
            break;
        case 2:                 // Green
            printf("\033[42m");
            break;
        case 3:                 // Yellow
            printf("\033[43m");
            break;
        case 4:                 // Blue
            printf("\033[44m");
            break;
        case 5:                 // Magenta
            printf("\033[45m");
            break;
        case 6:                 // Cyan
            printf("\033[46m");
            break;
        case 7:                 // White
            printf("\033[47m");
            break;
        default:
            printf("Invalid colour code '%d'.", id);
            printf("Valid colour codes: 0-8.\n");
            exit(EXIT_FAILURE);
    }

}
void resetColour() {

    printf("\033[0m"); 

}

#endif